#pragma once
#include <iostream>
#include <string>

class word_counter
{
public:
    class wc_node
    {
        std::string value;
        unsigned int cnt = 0;
        wc_node *next = nullptr;

        wc_node(std::string const& word, unsigned int count, wc_node* nxt);
        void set_next(wc_node * nxt);
        friend class word_counter;
    public:
        std::string const& get_value() const;
        unsigned int get_count() const;
        unsigned int & get_count();
        wc_node const* get_next() const;
    };

    word_counter();
    word_counter(word_counter const& wc);
    ~word_counter();

    word_counter& operator=(word_counter const& wc);
    word_counter& operator+=(word_counter const& wc);

    bool is_empty() const;
    unsigned int size() const;
    void pop_front();
    void clear();

    unsigned int operator[](std::string const& word) const;
    unsigned int & operator[](std::string const& word);
    wc_node const* get_first() const;

private:
    wc_node * wc_head = nullptr;
};



std::ostream& operator<<(std::ostream& os, word_counter::wc_node const& wcn);
std::ostream& operator<<(std::ostream& os, word_counter const& wc);
word_counter operator+(word_counter const& left_wc, word_counter const& right_wc);

