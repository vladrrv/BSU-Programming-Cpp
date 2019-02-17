using namespace std;

class Route
{
	int num;
	string name;
	int bus;
	string model;
public:
	Route();
	Route(int, string, int, string);
	Route(const Route &);
	string driver() const;
	int getbus() const;
	string getmodel() const;
	int getroute() const;
	void changebus(int);
	void changeroute(int);
	void info() const;
	friend bool operator<(const Route&, const Route&);
	bool operator==(const Route&);
};

Route::Route() : num(0), bus(0)
{
	name = "No_info";
	model = "No_info";
}
Route::Route(const Route &st)
{
	num = st.num;
	name = st.name;
	bus = st.bus;
	model = st.model;
}
Route::Route(int nu, string n, int b, string m)
{
	num = nu;
	name = n;
	bus = b;
	model = m;
}
int Route::getroute() const
{
	return num;
}
string Route::driver() const
{
	return name;
}
int Route::getbus() const
{
	return bus;
}
string Route::getmodel() const
{
	return model;
}
void Route::info() const
{
	cout << "Route: " << num << "\tDriver: " << name << "\tBus: " << bus << "\tBus model: " << model << endl;
}

void Route::changebus(int new_bus)
{
	bus = new_bus;
};

void Route::changeroute(int new_route)
{
	num = new_route;
};

bool operator<(const Route& s1, const Route& s2)
{
	return s1.getbus() < s2.getbus();
};

bool Route::operator==(const Route& s1)
{
	return getroute() == s1.getroute();
};