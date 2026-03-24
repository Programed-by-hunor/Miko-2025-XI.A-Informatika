#include <SFML/Graphics.hpp>
#include <cmath>

using namespace sf;

const float pi = 3.141592;

class Turtle
{
    VertexArray lines;  //array of line segments
    Vector2f pos;       //position
    Vector2f dir;       //direction
    float angle;        //turn angle in degrees
    float ratio;        //segment length change ratio

    //rotate around origo
    Vector2f rotate(Vector2f a, float angle)
    {
        float rad = angle * pi / 180;
        return Vector2f(
                        a.x * cos(rad) - a.y * sin(rad),
                        a.x * sin(rad) + a.y * cos(rad)
                    );
    }
public:
    Turtle(Vector2f startPos =  Vector2f(0, 0), Vector2f dir = Vector2f(50, 0), float angle = 30, float ratio = 2) : lines(Lines)
    {
        this->pos = startPos;
        this->dir = dir;
        this->angle = angle;
        this->ratio = ratio;
    }
    void move()
    {
        pos += dir;
    }
    void draw()
    {
        lines.append(Vertex(pos, Color::Red));
        move();
        lines.append(Vertex(pos, Color::Red));
    }
    void turnR()
    {
        dir = rotate(dir, angle);
    }
    void turnL()
    {
        dir = rotate(dir, -angle);
    }
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

    //csillag
    Turtle s5(Vector2f(500.f, 300.f), Vector2f(80.f, 0.f), 144, 1);

    for (int i = 0; i < 5; i++)
    {
        s5.draw();
        s5.turnR();
    }

    Turtle s(Vector2f(600.f, 200.f), Vector2f(80.f, 0.f), 144, 1.05);
    for (int i = 0; i < 20; i++)
    {
        s.draw();
        s.turnR();
        s.increase();
    }

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

        window.display();
    }

    return 0;
}
