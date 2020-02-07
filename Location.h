class Location{
	float x;
	float y;
	public:
	Location(float x=0.0,float y=0.0);
	void setX(float x);
	void setY(float y);
	void set(float x,float y);
	float getX() const;
	float getY() const;
	bool operator==(const Location& loc);
};
