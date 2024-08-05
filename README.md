# Millionaires-Game-Show
Project was carried out as part of the student scientific circle "Ruch Projektantów Gier" at Poznań University of Technology.

## General description of the project
Game was heavily inspired by "Who Wants to Be a Millionaire" television game show. Project is based on [SDL2 library](https://www.libsdl.org/) for C++ and uses [original graphics](images). 
Question database is stored in a [json file](data/database.json) and is loaded using [JSON for Modern C++](https://github.com/nlohmann/json) library. <br />
As in the original, the game gets more difficult as the show goes on. The player is offered 3 lifelines "50:50", "Phone a Friend" and "Ask the Audience". 
"Phone a Friend" and "Ask the Audience" are designed not to always give the right answer. The harder the question the higher the chance for a mistake.

## Link to scientific circle
[Ruch Projektantów Gier](https://www.facebook.com/ruchprojektantowgier)
