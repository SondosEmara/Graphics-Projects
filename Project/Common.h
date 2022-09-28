#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED
struct Vector
{
    double v[2];
    Vector(double x = 0, double y = 0)
    {
        v[0] = x;
        v[1] = y;
    }
    double& operator[](int i)
    {
        return v[i];
    }
};
int Round(double x)
{
    return (int)(x + 0.5);
}
void swap(int& x1, int& y1, int& x2, int& y2)
{
    int tmp = x1;
    x1 = x2;
    x2 = tmp;
    tmp = y1;
    y1 = y2;
    y2 = tmp;
}


Vector points[7];
int index=0;
#endif // COMMON_H_INCLUDED
