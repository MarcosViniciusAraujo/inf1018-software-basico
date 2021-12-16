float valfoo(double a, float b, int c, double d, float e){
	
	float r = (float)(c*d - a*b);
	if(r > e)
		return r;
	else 
		return d;
	
}