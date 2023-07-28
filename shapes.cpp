#include "shapes.hpp"

bool collide(Rectangle rectangle1, Rectangle rectangle2){
    for(double x = rectangle1.x ; x < rectangle1.x+rectangle1.width ; x++)
        for(double y = rectangle1.y ; y < rectangle1.y+rectangle1.height ; y++)
            if(collide(rectangle2, Point{x, y}))
                return true; 
    return false;
}

bool collide(Rectangle rectangle, Point point){
    return point.x > rectangle.x && point.x < rectangle.x + rectangle.width && point.y > rectangle.y && point.y < rectangle.y + rectangle.height;
}

bool collide(Rectangle rectangle, Circle circle){
    for(double x = rectangle.x ; x < rectangle.x+rectangle.width ; x++)
        for(double y = rectangle.y ; y < rectangle.y+rectangle.height ; y++)
            if(collide(circle, Point{x, y}))
                return true;
    return false;
}

bool collide(Circle circle1, Circle circle2){
    return (circle1.center.x-circle2.center.x)*(circle1.center.x-circle2.center.x)+(circle1.center.y-circle2.center.y)*(circle1.center.y-circle2.center.y) < (circle1.radius+circle2.radius)*(circle1.radius+circle2.radius);
}

bool collide(Circle circle, Point point){
    return (circle.center.x-point.x)*(circle.center.x-point.x)+(circle.center.y-point.y)*(circle.center.y-point.y) <= circle.radius*circle.radius;
}