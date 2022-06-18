#include "word_counter.h"

word_counter::word_counter(){
    wc_head = nullptr;
}

word_counter::wc_node::wc_node(std::string const& word, unsigned int count, wc_node* nxt){
    this->value = word;
    this->cnt = count;
    this->next = nxt;
}

void word_counter::wc_node::set_next(wc_node *nxt){
    this->next = nxt;
}

std::string const &word_counter::wc_node::get_value() const{
    return value;
}

unsigned int word_counter::wc_node::get_count() const{
    return cnt;
}

unsigned int &word_counter::wc_node::get_count(){
    return cnt;
}

word_counter::wc_node const *word_counter::wc_node::get_next() const{
    return next;
}

word_counter::word_counter(word_counter const& wc){

    wc_head = nullptr;
    *this = wc;
}

void word_counter::pop_front(){
    if(wc_head != nullptr){
        wc_node* new_head = wc_head->next;
        delete wc_head;
        wc_head = new_head;
    }
}

void word_counter::clear(){
    while(wc_head)
        pop_front();
}

word_counter::~word_counter(){
    clear();
}

bool word_counter::is_empty() const{
    if(wc_head == nullptr)
        return true;
    else
        return false;
}

const word_counter::wc_node* word_counter::get_first() const{
    return wc_head;
}

unsigned int word_counter::size() const{
    unsigned int size = 0;
    wc_node* count = wc_head;
    while(count){
        count = count->next;
        ++size;
    }
    return size;
}

word_counter& word_counter::operator=(word_counter const& other) {
    if(&other == this)
        return *this;
    clear();

    wc_node* prev = nullptr;
    wc_node* temp = other.wc_head;
    while(temp){
        wc_node* new_node = new wc_node(temp->value, temp->cnt, temp->next);

        if(wc_head == nullptr)
            wc_head = new_node;
        else
            prev->next = new_node;

        prev = new_node;
        temp = temp->next;
    }
    return *this;
}

std::ostream& operator<<(std::ostream& os, word_counter::wc_node const& wcn){

    os << "("<< wcn.get_value()<< " : "<< wcn.get_count()<< ") ";
    return os;
}

std::ostream& operator<<(std::ostream& os, word_counter const& wc){
    os<<"[";
    const word_counter::wc_node *ptr = wc.get_first();

    while (ptr)
    {
        os << *ptr;
        ptr = ptr->get_next();
    }
    os << "]";

    return os;
}

unsigned int word_counter::operator[](std::string const &word) const{
    wc_node *node = wc_head;

    while (node)
    {
        if (node->value == word)
        {
            return node->cnt;
        }
        node = node->next;
    }

    return 0;
}

unsigned int& word_counter::operator[](std::string const &word)
{
    wc_node *temp = wc_head;
    wc_node *prev = nullptr;
    while (temp)
    {
        if (temp->value == word)
            return temp->cnt;

        if (temp->value > word)
            break;

        prev = temp;
        temp = temp->next;
    }

    wc_node *new_node = new wc_node(word, 0, temp);

    if (prev == nullptr)
        wc_head = new_node;
    else
        prev->next = new_node;

    return new_node->cnt;
}

word_counter& word_counter::operator+=(word_counter const& wc) {

    wc_node const *node = wc.wc_head;

    while (node)
    {
        (*this)[node->value] += node->cnt;
        node = node->next;
    }
    return *this;
}

word_counter operator+(word_counter const& left_wc, word_counter const& right_wc){

    word_counter new_node = left_wc;
    new_node += right_wc;
    return new_node;

}
