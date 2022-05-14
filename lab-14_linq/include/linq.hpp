#pragma once

#include <utility>
#include <vector>
#include <functional>

namespace linq {
    namespace impl {

        template<typename T, typename Iter>
        class range_enumerator;

        template<typename T>
        class drop_enumerator;

        template<typename T, typename U, typename F>
        class select_enumerator;

        template<typename T, typename F>
        class until_enumerator;

        template<typename T, typename F>
        class where_enumerator;

        template<typename T>
        class take_enumerator;

        template<typename T>
        class enumerator {
        public:
            virtual T operator*() const = 0; // Получает текущий элемент.

            virtual enumerator &operator++() = 0;  // Переход к следующему элементу
            virtual operator bool() const = 0;  // Возвращает true, если есть текущий элемент

            auto drop(size_t count) {
                return drop_enumerator(*this, count);
            }

            template<typename U = T, typename F>
            auto select(F func) {
                return select_enumerator<U, T, F>(*this, func);
            }

            template<typename F>
            auto until(F func) {
                return until_enumerator(*this, func);
            }

            auto until_eq(const T &stop_value) {
                return until([=](const T &value) { return value == stop_value; });
            }

            template<typename F>
            auto where(F predicate) {
                return where_enumerator(*this, predicate);
            }

            auto where_neq(const T &forbidden_value) {
                return where([=](const T &value) { return value != forbidden_value; });
            }

            auto take(size_t count) {
                return take_enumerator(*this, count);
            }

            std::vector<T> to_vector() {
                std::vector<T> result;
                while (*this) {
                    result.emplace_back(**this);
                    ++(*this);
                }
                return result;
            }

            template<typename Iter>
            void copy_to(Iter it) {
                while (*this) {
                    *it = **this;
                    ++it;
                    ++(*this);
                }
            }
        };

        template<typename T, typename U = T>
        class derived_enumerator : public enumerator<T> {
        public:
            derived_enumerator(enumerator<U> &parent) : parent_(parent) {}

            T operator*() const override {
                return *parent_;
            }

            enumerator<T> &operator++() override {
                ++parent_;
                return *this;
            }

            operator bool() const override {
                return bool(parent_);
            }

        protected:
            enumerator<U> &parent_;
        };

        template<typename T, typename Iter>
        class range_enumerator : public enumerator<T> {
        public:
            range_enumerator(Iter begin, Iter end) : begin_(begin), end_(end) {}

            T operator*() const override {
                return *begin_;
            }

            range_enumerator &operator++() override {
                ++begin_;
                return *this;
            }

            operator bool() const override {
                return begin_ != end_;
            }

        private:
            Iter begin_, end_;
        };

        template<typename T>
        class drop_enumerator : public derived_enumerator<T> {
        public:
            drop_enumerator(enumerator<T> &parent, size_t count) : derived_enumerator<T>(parent) {
                for (size_t i = 0; i < count && this->parent_; ++i)
                    ++this->parent_;
            }
        };

        template<typename T, typename U, typename F>
        class select_enumerator : public derived_enumerator<T, U> {
        public:
            select_enumerator(enumerator<U> &parent, F func) : derived_enumerator<T, U>(parent),
                                                               func_(std::move(func)) {}

            T operator*() const override {
                return func_(*this->parent_);
            }

        private:
            F func_;
        };

        template<typename T, typename F>
        class until_enumerator : public derived_enumerator<T> {
        public:
            until_enumerator(enumerator<T> &parent, F predicate) : derived_enumerator<T>(parent),
                                                                   predicate_(std::move(predicate)),
                                                                   is_end_(predicate_(parent)) {}

            until_enumerator &operator++() override {
                ++this->parent_;
                is_end_ |= !this->parent_ || predicate_(*this->parent_);
                return *this;
            }

            operator bool() const override {
                return !is_end_;
            }

        private:
            F predicate_;
            bool is_end_;
        };

        template<typename T, typename F>
        class where_enumerator : public derived_enumerator<T> {
        public:
            where_enumerator(enumerator<T> &parent, F predicate) : derived_enumerator<T>(parent),
                                                                   predicate_(std::move(predicate)) {
                while (this->parent_ && !predicate(*this->parent_))
                    ++this->parent_;
            }

            where_enumerator &operator++() override {
                do {
                    ++this->parent_;
                } while (this->parent_ && !predicate_(*this->parent_));
                return *this;
            }

        private:
            F predicate_;
        };

        template<typename T>
        class take_enumerator : public derived_enumerator<T> {
        public:
            take_enumerator(enumerator<T> &parent, size_t count) : derived_enumerator<T>(parent), count_(count) {}

            take_enumerator &operator++() override {
                ++this->parent_;
                --count_;
                return *this;
            }

            operator bool() const override {
                return count_ && this->parent_;
            }

        private:
            size_t count_;
        };

    } // namespace impl

    template<typename T>
    auto from(T begin, T end) {
        return impl::range_enumerator<typename std::iterator_traits<T>::value_type, T>(begin, end);
    }

} // namespace linq
