mSize=0.025;
boxLength = 0.584;
boxHeight = 0.70;

Point(1) = {0.0, 0.0, 0, mSize};
Point(2) = {0.0, boxHeight, 0,mSize};
Point(3) = {boxLength, boxHeight, 0,mSize};
Point(4) = {boxLength, 0.0, 0,mSize};

Line(11) = {1, 2}; //left
Line(12) = {2, 3}; //top
Line(13) = {3, 4}; //right
Line(14) = {4, 1}; //bottom

Line Loop(31) = {-14, -13, -12, -11}; //front

Plane Surface(41) = {31}; //bottom


