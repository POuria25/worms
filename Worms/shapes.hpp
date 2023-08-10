#ifndef SHAPES_HPP__
#define SHAPES_HPP__

/**
 * @brief Point structure with x and y coordinate
 * 
 */
struct Point
{
    double x, y;
};

/**
 * @brief Rectangle structure with width, heigth, x and y coordinates
 * 
 */
struct Rectangle
{
    double x, y, width, height;
};

/**
 * @brief Circle structure with center point and radius
 * 
 */
struct Circle
{
    Point center;
    double radius;
};


/**
 * @brief Checks if any point within rectangle1 collides with rectangle2 by iterating over the points in rectangle1 and 
 *        using the collide(Rectangle rectangle, Point point) function.
 * @param rectangle1 
 * @param rectangle2 
 * @return true 
 * @return false 
 */
bool collide(Rectangle rectangle1, Rectangle rectangle2);


/**
 * @brief Determines whether a point lies inside the given rectangle by checking if the point's coordinates fall within 
 * the bounds of the rectangle.
 * 
 * @param rectangle 
 * @param point 
 * @return true 
 * @return false 
 */
bool collide(Rectangle rectangle, Point point);

/**
 * @brief Checks if any point within rectangle collides with the circle by iterating over the points in rectangle and using 
 * the collide(Circle circle, Point point) function.
 * 
 * @param rectangle 
 * @param circle 
 * @return true 
 * @return false 
 */
bool collide(Rectangle rectangle, Circle circle);

/**
 * @brief Determines if two circles, circle1 and circle2, collide by calculating the squared distance between their centers 
 * and comparing it to the sum of their squared radi.
 * 
 * @param circle1 
 * @param circle2 
 * @return true 
 * @return false 
 */
bool collide(Circle circle1, Circle circle2);

/**
 * @brief Checks if a point collides with the circle by calculating the squared distance between the point and the center of 
 * the circle and comparing it to the square of the circle's radius.
 * 
 * @param circle 
 * @param point 
 * @return true 
 * @return false 
 */
bool collide(Circle circle, Point point);

#endif