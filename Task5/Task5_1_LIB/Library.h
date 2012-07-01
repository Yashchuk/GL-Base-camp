struct LineSegment
{
	float a, b;
	bool empty;
};

void makeLineSegmentEpty(LineSegment &ls);

bool isEmpty(LineSegment &ls);

LineSegment createLineSegment(float a, float b);

LineSegment getLineCrossingSegment(LineSegment &ls1, LineSegment &ls2);
