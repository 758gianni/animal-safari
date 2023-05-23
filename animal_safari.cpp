// Program: Animal Safari Board Game
// By: Gianni Belizaire

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

#ifdef _WIN32
#define CLEAR_SCREEN system("cls")
#endif

#ifdef __APPLE__
#define CLEAR_SCREEN system("clear")
#endif

int main()
{
    // Random function
    srand((unsigned)time(0));

    // Clear screen
    CLEAR_SCREEN;

    // Declare Size of Board
    const int BOARD_SIZE = 100;

    // Lines from text files
    string binoculars_file_line = "";
    string compass_file_line = "";

    // Array to store cards from text files
    string binoculars_cards[25] = {};
    string compass_cards[20] = {};

    // Stores if there is a current winner
    bool current_winner = false;

    // Stores binocular and compass board positions
    int binoculars_spaces[9] = {8, 13, 31, 47, 52, 67, 72, 87, 93};
    int compass_spaces[9] = {12, 17, 35, 51, 56, 71, 76, 91, 97};

    // Stores player position
    int player_1_pos = 0;
    int player_2_pos = 0;

    // Stores player's dice roll results
    int player_1_dice_roll = 0;
    int player_2_dice_roll = 0;

    // Keeps track of how many animal cards players have
    int player_1_animal_card_count = 0;
    int player_2_animal_card_count = 0;

    // Store player animal cards
    string player_1_binoculars_cards[10] = {};
    string player_2_binoculars_cards[10] = {};

    // Binoculars.txt & Compass.txt files must be in the same directory as animal_safari.txt !
    ifstream binoculars("Binoculars.txt", fstream::out);
    ifstream compass("Compass.txt", fstream::out);

    // Open and read Binoculars.txt file
    if (!binoculars)
    {
        // Error opening Binoculars.txt
        cerr << "Error: Could not open Binoculars.txt!\nPlease make sure Binoculars.txt file is in the same directory as the animal_safari.cpp file!\n";
        return 1;
    }
    else
    {
        // Stores Binoculars.txt cards in array
        int i = 0;

        while (getline(binoculars, binoculars_file_line))
        {
            binoculars_cards[i++] = binoculars_file_line;
        }

        binoculars.close();
    }

    // Open and read Compass.txt file
    if (!compass)
    {
        // Error opening Compass.txt
        cerr << "Error: Could not open Compass.txt!\nPlease make sure Compass.txt file is in the same directory as the animal_safari.cpp file!\n";
        return 1;
    }
    else
    {
        // Stores Compass.txt cards in array
        int i = 0;

        while (getline(compass, compass_file_line))
        {
            compass_cards[i++] = compass_file_line;
        }

        compass.close();
    }

    // Introduction/Instructions
    cout << "+----- Welcome to Animal Safari Board Game! -----+\n\n";
    cout << "CIT102 Project: Animal Safari Project\n\n";
    cout << "Created By: Gianni Belizaire\n\n";
    cout << "Instructions:\n\n";
    cout << "Players take turns rolling the die & moving the number of spaces indicated on the die.\n\n";
    cout << "If a player lands on a compass space, they must draw a card & follow the directions given.\n\n";
    cout << "If a player lands on a binoculars space, they must draw a card from the deck of animal cards.\n\n";
    cout << "The first player to collect five animal cards & reach the finish space wins the game.\n\n";
    cout << "NOTE: Add values on the bottom row to values in the left column to get player position!\n\n";

    cout << "Press Enter to Continue...";
    cin.get(); // Wait for the User to Press Enter

    // Clear screen
    CLEAR_SCREEN;

    // Number of Spaces on Board: 100
    while (!current_winner)
    {
        // -- PLAYER 1 TURN --
        cout << "\n-- Player 1's Turn --\n\n";

        // Player 1 - Generate Random Dice Roll
        player_1_dice_roll = (rand() % 6) + 1;

        cout << "Player 1 Dice Roll: " << player_1_dice_roll << endl;

        // Player 1 - Move N Number of Spaces
        player_1_pos = player_1_pos + player_1_dice_roll;

        // Display player 1 position
        cout << "Player 1 Position: " << player_1_pos << endl;

        // If player 1 won
        if (player_1_pos >= 100 && player_1_animal_card_count >= 5)
        {
            // Clear screen
            CLEAR_SCREEN;

            cout << "+-------------------- WINNER --------------------+\n";
            cout << "Congratulations Player 1, has won the game!\n";
            cout << "Player 1 got to position 100 & has 5 animal cards!\n";
            cout << "Player 1 Position: " << player_1_pos << "!\n";

            cout << "Animal Cards Collected:\n";

            for (int i = 0; i < player_1_animal_card_count; i++)
            {
                cout << player_1_binoculars_cards[i] << endl;
            }

            cout << "\n+-------------------- LOOSER --------------------+\n";
            cout << "Player 2, lost the game :(\n";
            cout << "Player 2 Position: " << player_2_pos << "!\n";

            if (player_2_animal_card_count > 0)
            {
                cout << "Animal Cards Collected:\n";

                for (int i = 0; i < player_2_animal_card_count; i++)
                {
                    if (player_2_binoculars_cards[i] == "")
                    {
                        cout << endl;
                    }
                    else
                    {
                        cout << player_2_binoculars_cards[i] << endl;
                    }
                }
            }
            else
            {
                cout << "No Animal Cards Were Collected\n";
            }

            current_winner = true;

            break;
        }
        else
        {
            for (int i = 0; i < 9; i++)
            {
                // If Player 1 Lands on Binoculars Space, Draw a Card from the Deck of Animal Cards
                // The card will state what animals are received
                if (player_1_pos == binoculars_spaces[i])
                {
                    int rand_int = (rand() % 25);
                    string chosen_card = binoculars_cards[rand_int];

                    if (chosen_card == "You receive one random animal: Elephant")
                    {
                        player_1_binoculars_cards[player_1_animal_card_count] = "Elephant";
                        ++player_1_animal_card_count;
                    }
                    else if (chosen_card == "You receive two random animals: Kangaroo and Hippopotamus")
                    {
                        player_1_binoculars_cards[player_1_animal_card_count] = "Kangaroo";
                        player_1_binoculars_cards[player_1_animal_card_count + 1] = "Hippopotamus";
                        player_1_animal_card_count += 2;
                    }
                    else if (chosen_card == "You receive one random animal: Flamingo")
                    {
                        player_1_binoculars_cards[player_1_animal_card_count] = "Flamingo";
                        ++player_1_animal_card_count;
                    }
                    else if (chosen_card == "You receive two random animals: Crocodile and Gorilla")
                    {
                        player_1_binoculars_cards[player_1_animal_card_count] = "Crocodile";
                        player_1_binoculars_cards[player_1_animal_card_count + 1] = "Gorilla";
                        player_1_animal_card_count += 2;
                    }
                    else if (chosen_card == "You receive one random animal: Penguin")
                    {
                        player_1_binoculars_cards[player_1_animal_card_count] = "Penguin";
                        ++player_1_animal_card_count;
                    }
                    else if (chosen_card == "You receive two random animals: Zebra and Giraffe")
                    {
                        player_1_binoculars_cards[player_1_animal_card_count] = "Zebra";
                        player_1_binoculars_cards[player_1_animal_card_count + 1] = "Giraffe";
                        player_1_animal_card_count += 2;
                    }
                    else if (chosen_card == "You receive one random animal: Koala")
                    {
                        player_1_binoculars_cards[player_1_animal_card_count] = "Koala";
                        ++player_1_animal_card_count;
                    }
                    else if (chosen_card == "You receive two random animals: Lion and Tiger")
                    {
                        player_1_binoculars_cards[player_1_animal_card_count] = "Lion";
                        player_1_binoculars_cards[player_1_animal_card_count + 1] = "Tiger";
                        player_1_animal_card_count += 2;
                    }
                    else if (chosen_card == "You receive one random animal: Chimpanzee")
                    {
                        player_1_binoculars_cards[player_1_animal_card_count] = "Chimpanzee";
                        ++player_1_animal_card_count;
                    }
                    else if (chosen_card == "You receive two random animals: Dolphin and Whale")
                    {
                        player_1_binoculars_cards[player_1_animal_card_count] = "Dolphin";
                        player_1_binoculars_cards[player_1_animal_card_count + 1] = "Whale";
                        player_1_animal_card_count += 2;
                    }
                    else if (chosen_card == "You receive one random animal: Panda")
                    {
                        player_1_binoculars_cards[player_1_animal_card_count] = "Panda";
                        ++player_1_animal_card_count;
                    }
                    else if (chosen_card == "You receive two random animals: Rhino and Hyena")
                    {
                        player_1_binoculars_cards[player_1_animal_card_count] = "Rhino";
                        player_1_binoculars_cards[player_1_animal_card_count + 1] = "Hyena";
                        player_1_animal_card_count += 2;
                    }
                    else if (chosen_card == "You receive one random animal: Toucan")
                    {
                        player_1_binoculars_cards[player_1_animal_card_count] = "Toucan";
                        ++player_1_animal_card_count;
                    }
                    else if (chosen_card == "You receive two random animals: Snake and Lizard")
                    {
                        player_1_binoculars_cards[player_1_animal_card_count] = "Snake";
                        player_1_binoculars_cards[player_1_animal_card_count + 1] = "Lizard";
                        player_1_animal_card_count += 2;
                    }
                    else if (chosen_card == "You receive one random animal: Meerkat")
                    {
                        player_1_binoculars_cards[player_1_animal_card_count] = "Meerkat";
                        ++player_1_animal_card_count;
                    }
                    else if (chosen_card == "You receive two random animals: Armadillo and Anteater")
                    {
                        player_1_binoculars_cards[player_1_animal_card_count] = "Armadillo";
                        player_1_binoculars_cards[player_1_animal_card_count + 1] = "Anteater";
                        player_1_animal_card_count += 2;
                    }
                    else if (chosen_card == "You receive one random animal: Peacock")
                    {
                        player_1_binoculars_cards[player_1_animal_card_count] = "Peacock";
                        ++player_1_animal_card_count;
                    }
                    else if (chosen_card == "You receive two random animals: Penguin and Seal")
                    {
                        player_1_binoculars_cards[player_1_animal_card_count] = "Penguin";
                        player_1_binoculars_cards[player_1_animal_card_count + 1] = "Seal";
                        player_1_animal_card_count += 2;
                    }
                    else if (chosen_card == "You receive one random animal: Sloth")
                    {
                        player_1_binoculars_cards[player_1_animal_card_count] = "Sloth";
                        ++player_1_animal_card_count;
                    }
                    else if (chosen_card == "You receive two random animals: Camel and Ostrich")
                    {
                        player_1_binoculars_cards[player_1_animal_card_count] = "Camel";
                        player_1_binoculars_cards[player_1_animal_card_count + 1] = "Ostrich";
                        player_1_animal_card_count += 2;
                    }
                    else if (chosen_card == "You receive one random animal: Hedgehog")
                    {
                        player_1_binoculars_cards[player_1_animal_card_count] = "Hedgehog";
                        ++player_1_animal_card_count;
                    }
                    else if (chosen_card == "You receive two random animals: Fox and Raccoon")
                    {
                        player_1_binoculars_cards[player_1_animal_card_count] = "Fox";
                        player_1_binoculars_cards[player_1_animal_card_count + 1] = "Raccoon";
                        player_1_animal_card_count += 2;
                    }
                    else if (chosen_card == "You receive one random animal: Octopus")
                    {
                        player_1_binoculars_cards[player_1_animal_card_count] = "Octopus";
                        ++player_1_animal_card_count;
                    }
                    else if (chosen_card == "You receive two random animals: Crab and Lobster")
                    {
                        player_1_binoculars_cards[player_1_animal_card_count] = "Crab";
                        player_1_binoculars_cards[player_1_animal_card_count + 1] = "Lobster";
                        player_1_animal_card_count += 2;
                    }
                    else if (chosen_card == "You receive one random animal: Platypus")
                    {
                        player_1_binoculars_cards[player_1_animal_card_count] = "Platypus";
                        ++player_1_animal_card_count;
                    }

                    cout << "Player 1 Landed on a Binoculars Space (" << binoculars_spaces[i] << ")\n";
                    cout << chosen_card << endl;
                    cout << "Player 1 Now Has " << player_1_animal_card_count << " Animal Cards!\n";

                    break;
                }

                // If Player 1 Lands on Compass Space, Draw a Card & Follow the Directions Given
                // For Example, If Player Lands on "Move Forward 2 Spaces", They Must Move Forward 2 Spaces
                else if (player_1_pos == compass_spaces[i])
                {
                    int rand_int = (rand() % 20);
                    string chosen_compass_card = compass_cards[rand_int];

                    cout << "Player 1 Landed on a Compass Space (" << compass_spaces[i] << ")\n";
                    cout << chosen_compass_card << endl;

                    for (int i = 0; i < 20; i++)
                    {
                        if (chosen_compass_card == "Move forward 3 spaces.")
                        {
                            player_1_pos = player_1_pos + 3;
                            cout << "Player 1 New Position: " << player_1_pos << endl;
                            break;
                        }
                        else if (chosen_compass_card == "Move back 2 spaces.")
                        {
                            player_1_pos = player_1_pos - 2;
                            cout << "Player 1 New Position: " << player_1_pos << endl;

                            break;
                        }
                        else if (chosen_compass_card == "Give one animal away to the other player.")
                        {
                            if (player_1_animal_card_count > 0)
                            {
                                player_2_binoculars_cards[player_2_animal_card_count] = player_2_binoculars_cards[0];
                                ++player_2_animal_card_count;
                                --player_1_animal_card_count;

                                cout << "Player 1 gave one animal card to Player 2." << endl;
                            }
                            else
                            {
                                cout << "Player 1 has no animal cards to give." << endl;
                            }

                            break;
                        }
                        else if (chosen_compass_card == "Move forward 5 spaces.")
                        {
                            player_1_pos = player_1_pos + 5;
                            cout << "Player 1 New Position: " << player_1_pos << endl;

                            break;
                        }
                        else if (chosen_compass_card == "Steal one animal from the other player.")
                        {
                            if (player_2_animal_card_count > 0)
                            {
                                player_2_binoculars_cards[player_2_animal_card_count] = player_2_binoculars_cards[player_1_animal_card_count - 1];
                                --player_1_animal_card_count;
                                ++player_2_animal_card_count;
                                cout << "Player 2 stole one animal card from Player 1." << endl;
                            }
                            else
                            {
                                cout << "Player 2 has no animal cards to give." << endl;
                            }

                            break;
                        }
                        else if (chosen_compass_card == "Move back 1 space.")
                        {
                            player_1_pos = player_1_pos - 1;
                            cout << "Player 1 New Position: " << player_1_pos << endl;

                            break;
                        }
                        else if (chosen_compass_card == "Give two animals away to the other player.")
                        {
                            if (player_1_animal_card_count >= 2)
                            {
                                player_2_binoculars_cards[player_2_animal_card_count] = player_1_binoculars_cards[0];
                                ++player_2_animal_card_count;

                                player_2_binoculars_cards[player_2_animal_card_count] = player_1_binoculars_cards[1];
                                ++player_2_animal_card_count;
                                player_1_animal_card_count -= 2;

                                cout << "Player 1 gave two animal cards to Player 2." << endl;
                            }
                            else if (player_1_animal_card_count == 1)
                            {
                                player_2_binoculars_cards[player_2_animal_card_count] = player_1_binoculars_cards[0];
                                ++player_2_animal_card_count;
                                --player_1_animal_card_count;

                                cout << "Player 1 gave one animal card to Player 2." << endl;
                            }
                            else
                            {
                                cout << "Player 1 has no animal cards to give." << endl;
                            }

                            break;
                        }
                        else if (chosen_compass_card == "Move back 3 spaces.")
                        {
                            player_1_pos = player_1_pos - 3;
                            cout << "Player 1 New Position: " << player_1_pos << endl;

                            break;
                        }
                        else if (chosen_compass_card == "Steal two animals from the other player.")
                        {
                            if (player_2_animal_card_count >= 2)
                            {
                                for (int i = 0; i < 2; ++i)
                                {
                                    player_1_binoculars_cards[player_1_animal_card_count] = player_2_binoculars_cards[i];
                                    ++player_1_animal_card_count;
                                    --player_2_animal_card_count;
                                }

                                cout << "Player 1 stole two animal cards from Player 2." << endl;
                            }
                            else if (player_2_animal_card_count == 2)
                            {
                                player_1_binoculars_cards[player_1_animal_card_count] = player_2_binoculars_cards[0];
                                ++player_1_animal_card_count;
                                --player_2_animal_card_count;

                                cout << "Player 1 stole one animal card from Player 2." << endl;
                            }
                            else
                            {
                                cout << "Player 2 has no animal cards to give." << endl;
                            }

                            break;
                        }
                        else if (chosen_compass_card == "Move forward 4 spaces.")
                        {
                            player_1_pos = player_1_pos + 4;
                            cout << "Player 1 New Position: " << player_1_pos << endl;

                            break;
                        }
                        else if (chosen_compass_card == "Give three animals away to the other player.")
                        {
                            if (player_1_animal_card_count >= 3)
                            {
                                player_2_binoculars_cards[player_2_animal_card_count] = player_1_binoculars_cards[0];
                                player_2_binoculars_cards[player_2_animal_card_count + 1] = player_1_binoculars_cards[1];
                                player_2_binoculars_cards[player_2_animal_card_count + 2] = player_1_binoculars_cards[2];

                                player_2_animal_card_count += 3;
                                player_1_animal_card_count -= 3;

                                cout << "Player 1 gave three animal cards to Player 2." << endl;
                            }
                            else
                            {
                                cout << "Player 1 does not have enough animal cards to give." << endl;
                            }

                            break;
                        }
                        else if (chosen_compass_card == "Move forward 2 spaces.")
                        {
                            player_1_pos = player_1_pos + 2;
                            cout << "Player 1 New Position: " << player_1_pos << endl;

                            break;
                        }
                        else if (chosen_compass_card == "Move back 4 spaces.")
                        {
                            player_1_pos = player_1_pos - 4;
                            cout << "Player 1 New Position: " << player_1_pos << endl;

                            break;
                        }
                    }

                    break;
                }
            }

            if (player_1_pos >= 100 && player_1_animal_card_count < 5)
            {
                player_1_pos = 50;
                cout << "Player 1 reached position 100 but does not have 5 animal cards.\n";
                cout << "Player 1 was reset to position 50.\n";
            }

            // Draw the Board with the New Positions
            cout << endl;

            // Draw the Top Border of the Board
            cout << "   +-------------------- UPDATED BOARD --------------------+\n";

            // Draw Each Row of the Board
            for (int row = 0; row < BOARD_SIZE / 10; row++)
            {
                // Draw the Column Labels on the Left Side of the Board
                if (row * 10 == 0)
                {
                    cout << " " << 0 << "  |";
                }
                else
                {
                    cout << " " << row * 10 << " |";
                }

                // Draw Each Space on the Board
                for (int col = 0; col < 10; col++)
                {
                    int pos_num = row * 10 + col + 1;

                    if (pos_num == player_1_pos && pos_num == player_2_pos)
                    {
                        cout << "P1P2";
                    }

                    // Draw Player 1's Position If They Are on This Space
                    else if (pos_num == player_1_pos)
                    {
                        cout << " P1 ";
                    }

                    // Draw Player 2's Position If They Are on This Space
                    else if (pos_num == player_2_pos)
                    {
                        cout << " P2 ";
                    }

                    // Draw an Empty Space if Neither Player is on This Space
                    else
                    {
                        cout << "    ";
                    }

                    // Draw a Border Between Spaces
                    cout << "|";
                }

                // Draw the Bottom Border of the Row
                cout << "\n   +-------------------------------------------------------+\n";
            }

            // Draw the column labels at the bottom of the board
            cout << "      01   02   03   04   05   06   07   08   09   10\n";

            cout << "\nPress Enter to Continue...";
            cin.get(); // Wait for the User to Press Enter

            // Clear screen
            CLEAR_SCREEN;
        }

        // -- PLAYER 2 TURN --
        cout << "\n-- Player 2's Turn --\n\n";

        // Player 2 - Generate Random Dice Roll
        player_2_dice_roll = (rand() % 6) + 1;

        cout << "Player 2 Dice Roll: " << player_2_dice_roll << endl;

        // Player 2 - Move N Number of Spaces
        player_2_pos = player_2_pos + player_2_dice_roll;

        // Display player 2 position
        cout << "Player 2 Position: " << player_2_pos << endl;

        // If player 2 won
        if (player_2_pos >= 100 && player_2_animal_card_count >= 5)
        {
            // Clear screen
            CLEAR_SCREEN;

            cout << "+-------------------- WINNER --------------------+\n";
            cout << "Congratulations Player 2, has won the game!\n";
            cout << "Player 2 got to position 100 & has 5 animal cards!\n";
            cout << "Player 2 Position: " << player_2_pos << "!\n";

            cout << "Animal Cards Collected:\n";

            for (int i = 0; i < player_2_animal_card_count; i++)
            {
                cout << player_2_binoculars_cards[i] << endl;
            }

            cout << "\n+-------------------- LOOSER --------------------+\n";
            cout << "Player 1, lost the game :(\n";
            cout << "Player 1 Position: " << player_1_pos << "!\n";

            if (player_1_animal_card_count > 0)
            {
                cout << "Animal Cards Collected:\n";

                for (int i = 0; i < player_1_animal_card_count; i++)
                {
                    if (player_1_binoculars_cards[i] == "")
                    {
                        cout << endl;
                    }
                    else
                    {
                        cout << player_1_binoculars_cards[i] << endl;
                    }
                }
            }
            else
            {
                cout << "No Animal Cards Were Collected\n";
            }

            current_winner = true;

            break;
        }
        else
        {
            for (int i = 0; i < 9; i++)
            {
                // If Player 2 Lands on Binoculars Space, Draw a Card from the Deck of Animal Cards
                // The card will state what animals are received
                if (player_2_pos == binoculars_spaces[i])
                {
                    int rand_int = (rand() % 25);
                    string chosen_card = binoculars_cards[rand_int];

                    if (chosen_card == "You receive one random animal: Elephant")
                    {
                        player_2_binoculars_cards[player_2_animal_card_count] = "Elephant";
                        ++player_2_animal_card_count;
                    }
                    else if (chosen_card == "You receive two random animals: Kangaroo and Hippopotamus")
                    {
                        player_2_binoculars_cards[player_2_animal_card_count] = "Kangaroo";
                        player_2_binoculars_cards[player_2_animal_card_count + 1] = "Hippopotamus";
                        player_2_animal_card_count += 2;
                    }
                    else if (chosen_card == "You receive one random animal: Flamingo")
                    {
                        player_2_binoculars_cards[player_2_animal_card_count] = "Flamingo";
                        ++player_2_animal_card_count;
                    }
                    else if (chosen_card == "You receive two random animals: Crocodile and Gorilla")
                    {
                        player_2_binoculars_cards[player_2_animal_card_count] = "Crocodile";
                        player_2_binoculars_cards[player_2_animal_card_count + 1] = "Gorilla";
                        player_2_animal_card_count += 2;
                    }
                    else if (chosen_card == "You receive one random animal: Penguin")
                    {
                        player_2_binoculars_cards[player_2_animal_card_count] = "Penguin";
                        ++player_2_animal_card_count;
                    }
                    else if (chosen_card == "You receive two random animals: Zebra and Giraffe")
                    {
                        player_2_binoculars_cards[player_2_animal_card_count] = "Zebra";
                        player_2_binoculars_cards[player_2_animal_card_count + 1] = "Giraffe";
                        player_2_animal_card_count += 2;
                    }
                    else if (chosen_card == "You receive one random animal: Koala")
                    {
                        player_2_binoculars_cards[player_2_animal_card_count] = "Koala";
                        ++player_2_animal_card_count;
                    }
                    else if (chosen_card == "You receive two random animals: Lion and Tiger")
                    {
                        player_2_binoculars_cards[player_2_animal_card_count] = "Lion";
                        player_2_binoculars_cards[player_2_animal_card_count + 1] = "Tiger";
                        player_2_animal_card_count += 2;
                    }
                    else if (chosen_card == "You receive one random animal: Chimpanzee")
                    {
                        player_2_binoculars_cards[player_2_animal_card_count] = "Chimpanzee";
                        ++player_2_animal_card_count;
                    }
                    else if (chosen_card == "You receive two random animals: Dolphin and Whale")
                    {
                        player_2_binoculars_cards[player_2_animal_card_count] = "Dolphin";
                        player_2_binoculars_cards[player_2_animal_card_count + 1] = "Whale";
                        player_2_animal_card_count += 2;
                    }
                    else if (chosen_card == "You receive one random animal: Panda")
                    {
                        player_2_binoculars_cards[player_2_animal_card_count] = "Panda";
                        ++player_2_animal_card_count;
                    }
                    else if (chosen_card == "You receive two random animals: Rhino and Hyena")
                    {
                        player_2_binoculars_cards[player_2_animal_card_count] = "Rhino";
                        player_2_binoculars_cards[player_2_animal_card_count + 1] = "Hyena";
                        player_2_animal_card_count += 2;
                    }
                    else if (chosen_card == "You receive one random animal: Toucan")
                    {
                        player_2_binoculars_cards[player_2_animal_card_count] = "Toucan";
                        ++player_2_animal_card_count;
                    }
                    else if (chosen_card == "You receive two random animals: Snake and Lizard")
                    {
                        player_2_binoculars_cards[player_2_animal_card_count] = "Snake";
                        player_2_binoculars_cards[player_2_animal_card_count + 1] = "Lizard";
                        player_2_animal_card_count += 2;
                    }
                    else if (chosen_card == "You receive one random animal: Meerkat")
                    {
                        player_2_binoculars_cards[player_2_animal_card_count] = "Meerkat";
                        ++player_2_animal_card_count;
                    }
                    else if (chosen_card == "You receive two random animals: Armadillo and Anteater")
                    {
                        player_2_binoculars_cards[player_2_animal_card_count] = "Armadillo";
                        player_2_binoculars_cards[player_2_animal_card_count + 1] = "Anteater";
                        player_2_animal_card_count += 2;
                    }
                    else if (chosen_card == "You receive one random animal: Peacock")
                    {
                        player_2_binoculars_cards[player_2_animal_card_count] = "Peacock";
                        ++player_2_animal_card_count;
                    }
                    else if (chosen_card == "You receive two random animals: Penguin and Seal")
                    {
                        player_2_binoculars_cards[player_2_animal_card_count] = "Penguin";
                        player_2_binoculars_cards[player_2_animal_card_count + 1] = "Seal";
                        player_2_animal_card_count += 2;
                    }
                    else if (chosen_card == "You receive one random animal: Sloth")
                    {
                        player_2_binoculars_cards[player_2_animal_card_count] = "Sloth";
                        ++player_2_animal_card_count;
                    }
                    else if (chosen_card == "You receive two random animals: Camel and Ostrich")
                    {
                        player_2_binoculars_cards[player_2_animal_card_count] = "Camel";
                        player_2_binoculars_cards[player_2_animal_card_count + 1] = "Ostrich";
                        player_2_animal_card_count += 2;
                    }
                    else if (chosen_card == "You receive one random animal: Hedgehog")
                    {
                        player_2_binoculars_cards[player_2_animal_card_count] = "Hedgehog";
                        ++player_2_animal_card_count;
                    }
                    else if (chosen_card == "You receive two random animals: Fox and Raccoon")
                    {
                        player_2_binoculars_cards[player_2_animal_card_count] = "Fox";
                        player_2_binoculars_cards[player_2_animal_card_count + 1] = "Raccoon";
                        player_2_animal_card_count += 2;
                    }
                    else if (chosen_card == "You receive one random animal: Octopus")
                    {
                        player_2_binoculars_cards[player_2_animal_card_count] = "Octopus";
                        ++player_2_animal_card_count;
                    }
                    else if (chosen_card == "You receive two random animals: Crab and Lobster")
                    {
                        player_2_binoculars_cards[player_2_animal_card_count] = "Crab";
                        player_2_binoculars_cards[player_2_animal_card_count + 1] = "Lobster";
                        player_2_animal_card_count += 2;
                    }
                    else if (chosen_card == "You receive one random animal: Platypus")
                    {
                        player_2_binoculars_cards[player_2_animal_card_count] = "Platypus";
                        ++player_2_animal_card_count;
                    }

                    cout << "Player 2 Landed on a Binoculars Space (" << binoculars_spaces[i] << ")\n";
                    cout << chosen_card << endl;
                    cout << "Player 2 Now Has " << player_2_animal_card_count << " Animal Cards!\n";

                    break;
                }

                // If Player 2 Lands on Compass Space, Draw a Card & Follow the Directions Given
                // For Example, If Player Lands on "Move Forward 2 Spaces", They Must Move Forward 2 Spaces
                else if (player_2_pos == compass_spaces[i])
                {
                    int rand_int = (rand() % 20);
                    string chosen_compass_card = compass_cards[rand_int];

                    cout << "Player 2 Landed on a Compass Space (" << compass_spaces[i] << ")\n";
                    cout << chosen_compass_card << endl;

                    for (int i = 0; i < 20; i++)
                    {
                        if (chosen_compass_card == "Move forward 3 spaces.")
                        {
                            player_2_pos = player_2_pos + 3;
                            cout << "Player 2 New Position: " << player_2_pos << endl;
                            break;
                        }
                        else if (chosen_compass_card == "Move back 2 spaces.")
                        {
                            player_2_pos = player_2_pos - 2;
                            cout << "Player 2 New Position: " << player_2_pos << endl;

                            break;
                        }
                        else if (chosen_compass_card == "Give one animal away to the other player.")
                        {
                            if (player_2_animal_card_count > 0)
                            {
                                player_1_binoculars_cards[player_1_animal_card_count] = player_1_binoculars_cards[0];
                                ++player_1_animal_card_count;
                                --player_2_animal_card_count;

                                cout << "Player 2 gave one animal card to Player 1." << endl;
                            }
                            else
                            {
                                cout << "Player 2 has no animal cards to give." << endl;
                            }

                            break;
                        }
                        else if (chosen_compass_card == "Move forward 5 spaces.")
                        {
                            player_2_pos = player_2_pos + 5;
                            cout << "Player 2 New Position: " << player_2_pos << endl;

                            break;
                        }
                        else if (chosen_compass_card == "Steal one animal from the other player.")
                        {
                            if (player_1_animal_card_count > 0)
                            {
                                player_1_binoculars_cards[player_1_animal_card_count] = player_1_binoculars_cards[player_2_animal_card_count - 1];
                                --player_2_animal_card_count;
                                ++player_1_animal_card_count;
                                cout << "Player 1 stole one animal card from Player 2." << endl;
                            }
                            else
                            {
                                cout << "Player 1 has no animal cards to give." << endl;
                            }

                            break;
                        }
                        else if (chosen_compass_card == "Move back 1 space.")
                        {
                            player_2_pos = player_2_pos - 1;
                            cout << "Player 2 New Position: " << player_2_pos << endl;

                            break;
                        }
                        else if (chosen_compass_card == "Give two animals away to the other player.")
                        {
                            if (player_2_animal_card_count >= 2)
                            {
                                player_1_binoculars_cards[player_1_animal_card_count] = player_2_binoculars_cards[0];
                                ++player_1_animal_card_count;

                                player_1_binoculars_cards[player_1_animal_card_count] = player_2_binoculars_cards[1];
                                ++player_1_animal_card_count;
                                player_2_animal_card_count -= 2;

                                cout << "Player 2 gave two animal cards to Player 1." << endl;
                            }
                            else if (player_2_animal_card_count == 1)
                            {
                                player_1_binoculars_cards[player_1_animal_card_count] = player_2_binoculars_cards[0];
                                ++player_1_animal_card_count;
                                --player_2_animal_card_count;

                                cout << "Player 2 gave one animal card to Player 1." << endl;
                            }
                            else
                            {
                                cout << "Player 2 has no animal cards to give." << endl;
                            }

                            break;
                        }
                        else if (chosen_compass_card == "Move back 3 spaces.")
                        {
                            player_2_pos = player_2_pos - 3;
                            cout << "Player 2 New Position: " << player_2_pos << endl;

                            break;
                        }
                        else if (chosen_compass_card == "Steal two animals from the other player.")
                        {
                            if (player_1_animal_card_count >= 2)
                            {
                                for (int i = 0; i < 2; ++i)
                                {
                                    player_2_binoculars_cards[player_2_animal_card_count] = player_1_binoculars_cards[i];
                                    ++player_2_animal_card_count;
                                    --player_1_animal_card_count;
                                }

                                cout << "Player 2 stole two animal cards from Player 1." << endl;
                            }
                            else if (player_1_animal_card_count == 2)
                            {
                                player_2_binoculars_cards[player_2_animal_card_count] = player_1_binoculars_cards[0];
                                ++player_2_animal_card_count;
                                --player_1_animal_card_count;

                                cout << "Player 2 stole one animal card from Player 1." << endl;
                            }
                            else
                            {
                                cout << "Player 1 has no animal cards to give." << endl;
                            }

                            break;
                        }
                        else if (chosen_compass_card == "Move forward 4 spaces.")
                        {
                            player_2_pos = player_2_pos + 4;
                            cout << "Player 2 New Position: " << player_2_pos << endl;

                            break;
                        }
                        else if (chosen_compass_card == "Give three animals away to the other player.")
                        {
                            if (player_2_animal_card_count >= 3)
                            {
                                player_1_binoculars_cards[player_1_animal_card_count] = player_2_binoculars_cards[0];
                                player_1_binoculars_cards[player_1_animal_card_count + 1] = player_2_binoculars_cards[1];
                                player_1_binoculars_cards[player_1_animal_card_count + 2] = player_2_binoculars_cards[2];

                                player_1_animal_card_count += 3;
                                player_2_animal_card_count -= 3;

                                cout << "Player 2 gave three animal cards to Player 1." << endl;
                            }
                            else
                            {
                                cout << "Player 2 does not have enough animal cards to give." << endl;
                            }

                            break;
                        }
                        else if (chosen_compass_card == "Move forward 2 spaces.")
                        {
                            player_2_pos = player_2_pos + 2;
                            cout << "Player 2 New Position: " << player_2_pos << endl;

                            break;
                        }
                        else if (chosen_compass_card == "Move back 4 spaces.")
                        {
                            player_2_pos = player_2_pos - 4;
                            cout << "Player 2 New Position: " << player_2_pos << endl;

                            break;
                        }
                    }

                    break;
                }
            }

            if (player_2_pos >= 100 && player_2_animal_card_count < 5)
            {
                player_2_pos = 50;
                cout << "Player 2 reached position 100 but does not have 5 animal cards.\n";
                cout << "Player 2 was reset to position 50.\n";
            }

            // Draw the Board with the New Positions
            cout << endl;

            // Draw the Top Border of the Board
            cout << "   +-------------------- UPDATED BOARD --------------------+\n";

            // Draw Each Row of the Board
            for (int row = 0; row < BOARD_SIZE / 10; row++)
            {
                // Draw the Column Labels on the Left Side of the Board
                if (row * 10 == 0)
                {
                    cout << " " << 0 << "  |";
                }
                else
                {
                    cout << " " << row * 10 << " |";
                }

                // Draw Each Space on the Board
                for (int col = 0; col < 10; col++)
                {
                    int pos_num = row * 10 + col + 1;

                    if (pos_num == player_1_pos && pos_num == player_2_pos)
                    {
                        cout << "P1P2";
                    }

                    // Draw Player 1's Position If They Are on This Space
                    else if (pos_num == player_1_pos)
                    {
                        cout << " P1 ";
                    }

                    // Draw Player 2's Position If They Are on This Space
                    else if (pos_num == player_2_pos)
                    {
                        cout << " P2 ";
                    }

                    // Draw an Empty Space if Neither Player is on This Space
                    else
                    {
                        cout << "    ";
                    }

                    // Draw a Border Between Spaces
                    cout << "|";
                }

                // Draw the Bottom Border of the Row
                cout << "\n   +-------------------------------------------------------+\n";
            }

            // Draw the column labels at the bottom of the board
            cout << "      01   02   03   04   05   06   07   08   09   10\n";

            cout << "\nPress Enter to Continue...";
            cin.get(); // Wait for the User to Press Enter

            // Clear screen
            CLEAR_SCREEN;
        }
    }

    return 0;
}
