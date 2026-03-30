#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

using namespace sf;

const float pi = 3.141592;
const int stringSize = 10000;

struct Rule
{
    char pattern;
    char rule[100];
};

struct TurtleState{
    Vector2f pos;       //position
    Vector2f dir;       //direction
    float angle;        //turn angle in degrees
    float ratio;        //segment length change ratio
    Color color;
};

class Turtle
{
    VertexArray lines;  //array of line segments
    Vector2f pos;       //position
    Vector2f dir;       //direction
    float angle;        //turn angle in degrees
    float ratio;        //segment length change ratio
    Color color;
    char commands[stringSize];
    Rule rules[10];
    int ruleCount;
    TurtleState stateStack[1000];
    int stackSize;

    //rotate around origo
    Vector2f rotate(Vector2f a, float angle)
    {
        float rad = angle * pi / 180;
        return Vector2f(
                        a.x * cos(rad) - a.y * sin(rad),
                        a.x * sin(rad) + a.y * cos(rad)
                    );
    }
    void stringCopy(char source[],char dest[]){

        //while(*dest++==*source++);

        while(*source!=0)
        {
            //*dest++=*source++;

            *dest=*source;
            dest++;
            source++;
        }
        *dest = 0;
    }
    void stringConcatenate(char source[], char dest[])
    {
        while(*dest!=0)
        {
            dest++;
        }

        while(*source!=0)
        {
            *dest=*source;
            dest++;
            source++;
        }
        *dest = 0;
    }

    void push(){
        stackSize++;
        TurtleState tmp;
        tmp.angle = angle;
        tmp.color=color;
        tmp.dir=dir;
        tmp.pos=pos;
        tmp.ratio=ratio;
        stateStack[stackSize]=tmp;
    }

    void pop(){
        if(stackSize <0)
            return;

        TurtleState tmp =stateStack[stackSize];
        angle = tmp.angle;
        color= tmp.color;
        dir= tmp.dir;
        pos= tmp.pos;
        ratio= tmp.ratio;
        stackSize--;
    }

public:
    Turtle(Vector2f startPos =  Vector2f(0, 0), Vector2f dir = Vector2f(50, 0), float angle = 30, float ratio = 2, Color color = Color::Red) : lines(Lines)
    {
        this->pos = startPos;
        this->dir = dir;
        this->angle = angle;
        this->ratio = ratio;
        this->color = color;
        commands[0] = 0;
        ruleCount = 0;
    }
    void move()
    {
        pos += dir;
    }
    void draw()
    {
        lines.append(Vertex(pos, color));
        move();
        lines.append(Vertex(pos, color));
    }
    void turnR()
    {
        dir = rotate(dir, angle);
    }
    void turnL()
    {
        dir = rotate(dir, -angle);
    }
    //rotate by 180 degrees
    void flip()
    {
        dir.x *= -1;
        dir.y *= -1;
    }
    void increase()
    {
        dir *= ratio;
    }
    void decrease()
    {
        dir *= 1 / ratio;
    }
    void print(RenderWindow &window)
    {
        window.draw(lines);
    }
    void setCommand(char *s)
    {
        stringCopy(s, commands);
    }
    void appendCommand(char *s)
    {
        stringConcatenate(s, commands);
    }
    void addRule(char c, char *s){
        Rule r;
        r.pattern = c;
        stringCopy(s, r.rule);
        rules[ruleCount] = r;
        ruleCount++;
    }
    void processCommands()
    {
        lines.clear();
        for(char *c = commands; *c; c++)
        {
            switch(*c)
            {
                case 'F': draw(); break;
                case 'G': draw(); break;
                case 'D': draw(); break;
                case 'M': move(); break;
                case 'f': move(); break;
                case '+': turnR(); break;
                case '-': turnL(); break;
                case '>': increase(); break;
                case '<': decrease(); break;
                case '|': flip(); break;
                case '[': push(); break;
                case ']': pop(); break;
            }
        }
    }
    //n iterations
    void applyRules(int n)
    {
        while(n > 0)
        {
            char newCommands[stringSize];
            newCommands[0] = 0;
            for (char *i = commands; *i; i++)
            {
                bool found = false;
                for(int j = 0; j < ruleCount; j++)
                {
                    if(rules[j].pattern == *i)
                    {
                        stringConcatenate(rules[j].rule, newCommands);
                        found = true;
                        break;
                    }
                }
                if(!found)
                {
                    char tmp[2];
                    tmp[0] = *i;
                    tmp[1] = 0;
                    stringConcatenate(tmp, newCommands);
                }
            }
            n--;
            stringCopy(newCommands, commands);
        }
        std::cout << commands << std::endl;
        processCommands();
    }
};

int main()
{
    int windowWidth = 800;
    int windowHeight = 600;
    RenderWindow window(VideoMode(windowWidth, windowHeight), "Lindenmayer system");
    window.setFramerateLimit(60);

    Turtle koch(Vector2f(100.f,400.f), Vector2f(3.f, 0.f), 90, 1, Color::White);
    koch.setCommand("F");
    koch.addRule('F', "F+F-F-F+F");
    koch.applyRules(4);

    Turtle sierpinski(Vector2f(500.f,500.f), Vector2f(10.f, 0.f), 120, 1, Color::Red);
    sierpinski.setCommand("F-G-G");
    sierpinski.addRule('F', "F-G+F+G-F");
    sierpinski.addRule('G', "GG");
    sierpinski.applyRules(4);

    Turtle tree(Vector2f(400.f,600.f), Vector2f(0.f, -2.f), 50, 1, Color::Green);
    tree.setCommand("F");
    tree.addRule('F', "G[-F][+F]");
    tree.addRule('G', "GG");
    tree.applyRules(8);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::KeyPressed)
            {
                if(event.key.code == Keyboard::Escape)
                    window.close();

                // Press a key to save screenshot
                if(event.key.code == Keyboard::S)
                {
                    Texture texture;
                    texture.create(window.getSize().x, window.getSize().y);
                    texture.update(window); // copy window contents

                    Image screenshot = texture.copyToImage();
                    screenshot.saveToFile("screenshot.png");
                }
            }
        }

        window.clear(Color::Black);

        sierpinski.print(window);
        koch.print(window);
        tree.print(window);

        window.display();
    }
    return 0;
}
