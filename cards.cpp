#include "cards.hh"

Cards::Cards():
    top_(nullptr)
{

}

Card_data *Cards::get_topmost()
{
    return top_;
}

void Cards::add(int id)
{
// Creates a new card and uses 'new', because otherwise memory is going to drain
// when leaving add method. Adds created top card to the top of the pile by
// pointing to the current top card.

    // Creates a new card and returns pointer
    Card_data *card = new Card_data;

    // New created card, parameter id value is given to card's data
    card->data = id;

    // Pile's new top card points to a current top card
    card->next = top_;

    // Pile's top card's pointer pointing to a current card
    top_ = card;

}

void Cards::print_from_top_to_bottom(std::ostream &s)
{
// Prints cards from the top to bottom.

    // Goes throw cards
    int index = 1;
    Card_data *current = top_;

    // The amount of cards is unknown so going throw every card can be done by
    // using while loop as long as the current card's value is not 'nullptr'
    while ( current != nullptr )
    {
        // Output stream (ostream) s takes the parameter index (which value is
        // raised by one every round), correct print ": " and current's data
        s << index++ << ": " << current->data << std::endl;

        // Every round current is changed to next card that is on top
        current = current->next;
    }

}

bool Cards::remove(int &id)
{
// Checks if the pile is empty. If so, returns false otherwise points the top
// card to be the card under the top card, deletes (releases the memory of) the
// top card and returns true. Parameter 'id' is given as a reference so the
// change is going to be seen in callfunction.

    // The pile is empty if the top card has value 'nullptr'
    if ( top_ == nullptr )
    {
        return false;
    }

    // Saves the card on top
    Card_data *top_card = top_;

    // The top card's pointer points to a next card in the pile
    top_ = top_card->next;

    // Saves the information of the card under the top card
    id = top_card->data;

    // Releases the information of the card that is on top
    delete top_card;

    // Returns true
    return true;

}

bool Cards::bottom_to_top()
{
// Checks if the pile is empty. If so, returns false otherwise moves the bottom
// card to the top.

    // The pile is empty if the top card has value 'nullptr'
    if ( top_ == nullptr )
    {
        return false;
    }

    // If the next card's value after the top card is 'nullptr', it means that
    // there is nothing after the top card and the pile has only one card
    if ( top_->next == nullptr )
    {
        return true;
    }

    Card_data *last = top_;
    Card_data *second_last;

    // Goes throw while loop as long as last cards value is not 'nullptr' and
    // updates the value for second_last card and last card
    while ( last->next != nullptr )
    {
        second_last = last;
        last = last->next;
    }

    // Moves the pointers to point to the correct cards meaning that the current
    // second_last becomes the next last and last points to the top card
    second_last->next = nullptr;
    last->next = top_;
    top_ = last;

    return true;

}

bool Cards::top_to_bottom()
{
// Checks if the pile is empty. If so, returns false otherwise moves the top
// card to the bottom.

    // The pile is empty if the top card has value 'nullptr'
    if ( top_ == nullptr )
    {
        return false;
    }

    // If the next card's value after the top card is 'nullptr', it means that
    // there is nothing after the top card and the pile has only one card
    if ( top_->next == nullptr )
    {
        return true;
    }

    Card_data *last = top_;
    Card_data *current_top = top_;

    // Goes throw while loop as long as last cards value is not 'nullptr' and
    // updates the value for last card
    while ( last->next != nullptr )
    {
        last = last->next;
    }

    // When moving the top card to bottom, the next top card is going to be the
    // card under the card on top and last card is going to be the card that was
    // on top of the pile which value is saved in current_top
    top_ = top_->next;
    last->next = current_top;
    current_top->next = nullptr;

    return true;

}

void Cards::print_from_bottom_to_top(std::ostream &s)
{
// If the top card's value is not 'nullptr', calls recursive print.

    if ( top_ != nullptr )
    {
        recursive_print(top_, s);
    }
}

Cards::~Cards()
{
// Goes throw cards and releases the memory.

    Card_data *current = top_;
    Card_data *temp;

    // Goes throw while loop as long as current card's value is not 'nullptr',
    // gives temp card current card's value and updates the value for current
    // card as a next card after the current card
    while ( current != nullptr )
    {
        temp = current;
        current = current->next;
        delete temp;
    }
}

int Cards::recursive_print(Card_data *top, std::ostream &s)
{
// Calls itself until there is no longer a card after current card.

    // Tailrecursive; calls the recursion first and then the print

    // In trivialcase there is no next card
    if ( top->next == nullptr )
    {
        s << 1 << ": " << top->data << std::endl;
        return 1;
    }

    // In non-trivial case the function is called
    int result = recursive_print(top->next, s);
    s << ++result << ": " << top->data << std::endl;
    return result;

}
