//Implemente como función independiente la
//sobrecarga del operador ‘ + ’ para una clase punto
//(puntos 2D).Compruebe el resultado mediante un test
//unitario apropia
#include <iostream>
#include <fstream>

using namespace std;

class Punto
{
	float x_ = 0.0f;
	float y_ = 0.0f;
public:
	Punto() = default;
	Punto(float x, float y) : x_(x), y_(y) {}
	~Punto() = default;

	float x() const { return x_; }
	float y() const { return y_; }
	void set_x(float x) { x_ = x; }
	void set_y(float y) { y_ = y; }

	//  distancia al origen
	float mod() const { return std::sqrt(x_ * x_ + y_ * y_); }

	friend Punto operator + (Punto lhs, const Punto& rhs);
	friend Punto operator + (float k, Punto lhs);
	friend Punto operator + (Punto lhs, float k);

	bool operator!() const { return (x_ == 0.0f && y_ == 0.0f); }

	// sobrecarga de comparadores (basados en la distancia al origen)
	friend bool operator <		(const Punto& lhs, const Punto& rhs);
	friend bool operator ==		(const Punto& lhs, const Punto& rhs);

	// resto de comparaciones a partir de las 2 anteriores
	friend bool operator !=		(const Punto& lhs, const Punto& rhs) { return !(lhs == rhs); }
	friend bool operator >		(const Punto& lhs, const Punto& rhs) { return  operator< (rhs, lhs); }
	friend bool operator <=		(const Punto& lhs, const Punto& rhs) { return !operator> (lhs, rhs); }
	friend bool operator >=		(const Punto& lhs, const Punto& rhs) { return !operator< (lhs, rhs); }

	friend std::ostream& operator<<(std::ostream& os, const Punto& p);
};

// operador + independiente definido mediante el operador += miembro
Punto operator + (Punto lhs, const Punto& rhs)
{
	lhs.x_ += rhs.x_;
	lhs.y_ += rhs.y_;
	return lhs;
}

Punto operator + (float k, Punto rhs) {
	rhs.x_ += k;
	rhs.y_ += k;
	return rhs;
}

Punto operator + (Punto lhs, float k) {
	lhs.x_ += k;
	lhs.y_ += k;
	return lhs;
}

std::ostream& operator<<(std::ostream& os, const Punto& p) {
	// Formato de salida: (x, y)
	os << "(" << p.x_ << ", " << p.y_ << ")\n";
	return os; // Permite hacer: cout << p1 << p2;
}

bool operator==(const Punto& lhs, const Punto& rhs)
{
	return (lhs.x_ == rhs.x_ && lhs.y_ == rhs.y_);
}

bool operator<(const Punto& lhs, const Punto& rhs)
{
	return lhs.mod() < rhs.mod();
}



// programa de prueba
int main()
{

	Punto p1(1.0f, 2.0f);
	Punto p2(3.0f, 4.0f);

	cout << "p1: " << p1;
	cout << "p2: " << p2;

	Punto p3 = p1 + p2;		// uso del operador + definido

	cout << "p3: " << p3;

	// ahora se pide al usuario que escriba por teclado dos puntos y se muestra su suma
	cout << "Introduce las coordenadas del primer punto (x y): ";
	float x1, y1;
	cin >> x1 >> y1;
	cout << "Introduce las coordenadas del segundo punto (x y): ";
	float x2, y2;
	cin >> x2 >> y2;
	Punto p4(x1, y1);
	Punto p5(x2, y2);
	cout << "p4: " << p4;
	cout << "p5: " << p5;
	Punto p6 = p4 + p5;
	cout << "p6: " << p6;

	// test del operador ! (punto nulo)
	Punto p7(0.0f, 0.0f);
	cout << "p7: " << p7;
	cout << "p7 es el punto nulo? " << (!p7 ? "Si" : "No") << "\n";
	Punto p8(1.0f, 0.0f);
	cout << "p8: " << p8;
	cout << "p8 es el punto nulo? " << (!p8 ? "Si" : "No") << "\n";

	// test de flujo a consola y fichero
	Punto p(3.5, 7.3);
	std::cout << p << std::endl; // Muestra en consola: (3.5, 7.2)

	std::ofstream archivo("puntos.txt");
	if (archivo.is_open()) {
		archivo << p << std::endl;
		archivo.close();
	}

	return 0;
}