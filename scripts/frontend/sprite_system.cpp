#include "sprite_system.hpp"
#include "text_manager.hpp"
#include "texture_manager.hpp"

Sprite::Sprite(const char* filename, int x, int y) : Object(x, y){
    tex = TextureManager::LoadTexture(filename);
    SDL_QueryTexture(tex, NULL, NULL, &width, &height);
    src.x = src.y = 0; 
    dest.x = pos.x;
    dest.y = pos.y;
    src.w = dest.w = width;
    src.h = dest.h = height;
}

void Sprite::draw() {
    TextureManager::Draw(tex, src, dest);
}

void Sprite::update(){
    // we are not changing sprite's position, so currently blank
};

int Sprite::getWidth(){
    return width;
}
int Sprite::getHeight(){
    return height;
}
SDL_Rect& Sprite::getPosition(){ return dest; }

Spritesheet::Spritesheet(const char* filename, int x, int y, int numOfColumns, int numOfRows) 
: Sprite(filename, x, y), numOfColumns(numOfColumns), numOfRows(numOfRows){
    src.x = (spriteWidth) * 0;     // during inicialization we set the sprite to first of a spritesheet  
    src.y = (spriteHeight) * 0;
    src.w = dest.w = spriteWidth;
    src.h = dest.h = spriteHeight;
}

// NOTE: when we will decide on the final form of the spritesheets this will probably have to be changed
void Spritesheet::updateSprite(int row, int col){
    src.x = (width / numOfColumns) * row;
    src.y = (height / numOfRows) * col;
}
int Spritesheet::getWidth(){
    return spriteWidth;
}
int Spritesheet::getHeight(){
    return spriteHeight;
}


TextSprite::TextSprite(const char* filename, int x, int y, std::string data, int numOfColumns, int numOfRows) 
        : Spritesheet(filename, x, y, numOfColumns, numOfRows){
    
    contents.dest.x += MOVE_HORIZONTALLY;
    
    loadData(data);
}
void TextSprite::loadData(std::string data){
    contents.text = data;

    font = TextManager::getInstance().getHugeFont();
    TTF_SizeText(font, contents.text.c_str(), &contents.dest.w, &contents.dest.h);
    if (contents.dest.w > dest.w - MOVE_HORIZONTALLY * 2){
        font = TextManager::getInstance().getLargeFont();
        TTF_SizeText(font, contents.text.c_str(), &contents.dest.w, &contents.dest.h);
        if (contents.dest.w > (dest.w - MOVE_HORIZONTALLY * 2) * 2 - 50){
            font = TextManager::getInstance().getMediumFont();
            TTF_SizeText(font, contents.text.c_str(), &contents.dest.w, &contents.dest.h);
        }
        if (contents.dest.w > dest.w - MOVE_HORIZONTALLY * 2){
            contents.dest.w = dest.w - MOVE_HORIZONTALLY * 2;
            contents.dest.h *= 2;
        }
    }
    // center the text (depending on the font might have to change the value of MOVE_VERTICALLY)
    contents.dest.y = (dest.h / 2) - (contents.dest.h / 2) + MOVE_VERTICALLY;

    textTexture = TextManager::getInstance().loadText(font, contents, dest);
}
void TextSprite::draw(){
    TextureManager::Draw(tex, src, dest);
    TextManager::getInstance().draw(textTexture, dest);
}


DoubleTextsprite::DoubleTextsprite(const char* filename, int x, int y, std::string prefixData, std::string data, std::string flush,
                int numOfColumns, int numOfRows) : Spritesheet(filename, x, y, numOfColumns, numOfRows), flush(flush){
    prefix.text = prefixData;

    TTF_SizeText(TextManager::getInstance().getMediumFont(), prefix.text.c_str(), &prefix.dest.w, &prefix.dest.h);
    prefix.dest.x += MOVE_HORIZONTALLY;
    prefix.dest.y += (dest.h / 2) - (prefix.dest.h / 2) + MOVE_VERTICALLY;
    contents.dest.x += MOVE_HORIZONTALLY * 2 + prefix.dest.w;

    loadData(data);
}
void DoubleTextsprite::loadData(std::string data){
    contents.text = data;

    font = TextManager::getInstance().getMediumFont();
    TTF_SizeText(font, contents.text.c_str(), &contents.dest.w, &contents.dest.h);
    if (contents.dest.w > dest.w - MOVE_HORIZONTALLY * 3 - prefix.dest.w){
        font = TextManager::getInstance().getSmallFont();
        TTF_SizeText(font, contents.text.c_str(), &contents.dest.w, &contents.dest.h);
    }
    // center the text (depending on the font might have to change the value of MOVE_VERTICALLY)
    contents.dest.y = (dest.h / 2) - (contents.dest.h / 2) + MOVE_VERTICALLY;
    if (font == TextManager::getInstance().getSmallFont()){
        contents.dest.y += ALIGN;
    }
    if (flush == "right"){
        contents.dest.x = dest.w - contents.dest.w - MOVE_HORIZONTALLY;
    }

    textTexture = TextManager::getInstance().loadText(font, contents, prefix, dest);
}

void DoubleTextsprite::draw(){
    TextureManager::Draw(tex, src, dest);
    TextManager::getInstance().draw(textTexture, dest);
}