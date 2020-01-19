class Location{
	float x;
	float y;
	public:
	Location(float x,float y);
	void setX(float x);
	void setY(float y);
	void set(float x,float y);
	float getX();
	float getY();
	bool operator==(const Location& loc);
};
