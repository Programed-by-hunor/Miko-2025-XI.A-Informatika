#include <SFML/Graphics.hpp>
#include <cmath>
#include <string>
#include <vector>

using namespace sf;

class Turtle
{
    const float pi = 3.141592;
    VertexArray lines;  //array of line segments
    Vector2f pos;       //position
    Vector2f dir;       //direction
    float angle;        //turn angle in degrees
    float ratio;        //segment length change ratio
    Color color;
    char commands[10000];

    //rotate around origo
    Vector2f rotate(Vector2f a, float angle)
    {
        float rad = angle * pi / 180;
        return Vector2f(
                        a.x * cos(rad) - a.y * sin(rad),
                        a.x * sin(rad) + a.y * cos(rad)
                    );
    }
    void stringCopy(char source[],char dest[])
    {
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
    }
public:
    Turtle(Vector2f startPos =  Vector2f(0, 0), Vector2f dir = Vector2f(50, 0), float angle = 30, float ratio = 2, Color color = Color::Red, char * s = 0) : lines(Lines)
    {
        this->pos = startPos;
        this->dir = dir;
        this->angle = angle;
        this->ratio = ratio;
        this->color = color;
        commands[0] = 0;
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
    void processCommands()
    {
        lines.clear();
        for (char *c = commands; *c; c++)
        {
            switch(*c)
            {
                case 'F': draw(); break;
                case 'G': draw(); break;
                case 'D': draw(); break;
                case 'M': move(); break;
                case '+': turnR(); break;
                case '-': turnL(); break;
                case '>': increase(); break;
                case '<': decrease(); break;
                case '|': flip(); break;
            }
        }
    }
};

int main()
{
    int windowWidth = 800;
    int windowHeight = 600;
    RenderWindow window(VideoMode(windowWidth, windowHeight), "Turtle Graphics");
    window.setFramerateLimit(60);

    Vector2f start(300.f, 300.f);
    Vector2f dir(50.f, 0.f);
    Turtle h(start, dir, 30, 1.5);

    //haziko
    h.draw();
    h.turnL();
    h.turnL();
    h.turnL();
    h.draw();
    h.turnL();
    h.draw();
    h.turnL();
    h.turnL();
    h.turnL();
    h.turnL();
    h.draw();
    h.turnL();
    h.turnL();
    h.turnL();
    h.turnL();
    h.draw();
    h.flip();
    h.move();
    h.turnL();
    h.turnL();
    h.turnL();
    h.draw();

    Turtle b(Vector2f(100.f, 100.f), Vector2f(40.f, 0.f), 72, 1);
    for(int i=0;i<5;i++)
    {
        b.draw();
        b.turnR();
    }

    //csillag
    Turtle s5(Vector2f(500.f, 300.f), Vector2f(80.f, 0.f), 144, 1);

    for (int i = 0; i < 5; i++)
    {
        s5.draw();
        s5.turnR();
    }

    //spiral csillag
    Turtle s(Vector2f(400.f, 200.f), Vector2f(80.f, 0.f), 144, 1.05);
    for (int i = 0; i < 20; i++)
    {
        s.draw();
        s.turnR();
        s.increase();
    }

    Turtle a(Vector2f(200.f, 100.f), Vector2f(100.f, 0.f), 90, 1.1, Color::Green);
    a.setCommand("D+D+D+D");
    a.processCommands();


    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::KeyPressed)
                //if (event.key.code == Keyboard::Escape)
                window.close();
        }

        window.clear(Color::Black);

        h.print(window);
        s5.print(window);
        s.print(window);
        b.print(window);
        a.print(window);

        window.display();
    }

    return 0;
}
