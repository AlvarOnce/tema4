/**
 * @file punto_sobrecarga_operadores.cpp
 * @brief Implementación de una clase 2D simple con sobrecarga de operadores.
 *
 * @details
 * Este fichero define e implementa la clase @c punto, que modela un punto del
 * plano mediante dos coordenadas cartesianas de tipo @c float.
 *
 * La clase ilustra varios conceptos básicos de programación orientada a objetos
 * en C++:
 * - uso del constructor por defecto y del constructor de copia generado
 *   por el compilador,
 * - definición de funciones miembro constantes,
 * - sobrecarga de operadores aritméticos, lógicos, relacionales y de texto,
 * - implementación canónica de operadores binarios a partir de @c operator+=.
 *
 * Los operadores de comparación se basan en la distancia del punto al origen.
 *
 * @author Pablo San Segundo, course Informática Industrial, ETSIDI, UPM
 * @date
 *  - creación:  2023-03-15
 *  - ultima modificación: 2026-03-09 11/04/2026
 */

#include <iostream>
#include <cmath>							// std::sqrt - “Si no incluyes lo que usas, tu código puede compilar… hasta que deje de hacerlo.”

class punto {

	////////////////
	// interfaz público
public:

	// constructores y asignación mediante copia
	punto() = default;								//	no cambia el comportamiento, pero hace explícita la intención del programador y protege frente a cambios futuros
	punto(const punto& p) = default;				//	no cambia el comportamiento, pero hace explícita la intención del programador y protege frente a cambios futuros
	punto& operator= (const punto& rhs) = default;	//	no cambia el comportamiento, pero hace explícita la intención del programador 


	//  distancia al origen
	float mod() const { return std::sqrt(x_ * x_ + y_ * y_); }

	//  sobrecarga de operadores monarios
	bool operator!() const { return (x_ == 0.0f && y_ == 0.0f); }

	// sobrecarga de operadores aritméticos	
	punto& operator += (const punto& rhs);
	punto& operator += (float k);
	friend punto operator + (punto lhs, const punto& rhs);		// forma canónica (función independiente), se construye a partir del +=

	friend punto operator + (float k, punto lhs);				// permite k + p
	friend punto operator + (punto lhs, float k);				// permite p + k

	// sobrecarga de comparadores (basados en la distancia al origen)
	friend bool operator <		(const punto& lhs, const punto& rhs);
	friend bool operator ==		(const punto& lhs, const punto& rhs);

	// resto de comparaciones a partir de las 2 anteriores
	friend bool operator !=		(const punto& lhs, const punto& rhs) { return !(lhs == rhs); }
	friend bool operator >		(const punto& lhs, const punto& rhs) { return  operator< (rhs, lhs); }
	friend bool operator <=		(const punto& lhs, const punto& rhs) { return !operator> (lhs, rhs); }
	friend bool operator >=		(const punto& lhs, const punto& rhs) { return !operator< (lhs, rhs); }


	//I/O
	std::ostream& print(std::ostream& o = std::cout) const;

	// sobrecarga del operador << (función independiente y amiga de la clase)
	friend std::ostream& operator <<(std::ostream& o, const punto& p) { p.print(o);  return o; }


	////////////////
	// estado
private:
	float x_ = 0.0f;
	float y_ = 0.0f;
};

punto& punto::operator += (const punto& rhs) {
	this->x_ += rhs.x_;
	this->y_ += rhs.y_;
	return *this;
}

punto operator + (punto lhs, const punto& rhs) {
	lhs += rhs;			// uso del operador += previamente definido
	return lhs;			// se devuelve por valor; el compilador puede optimizar la copia
}

punto& punto::operator += (float k) {
	this->x_ += k;
	this->y_ += k;
	return *this;
}

std::ostream& punto::print(std::ostream& o) const {
	o << "[" << x_ << "," << y_ << "]";
	return o;
}

punto operator + (float k, punto rhs) {
	rhs += k;
	return rhs;			// se devuelve por valor; el compilador puede optimizar la copia
}

punto operator + (punto lhs, float k) {
	lhs += k;
	return lhs;			// se devuelve por valor; el compilador puede optimizar la copia
}

bool operator==(const punto& lhs, const punto& rhs)
{
	return (lhs.x_ == rhs.x_ && lhs.y_ == rhs.y_);
}

bool operator<(const punto& lhs, const punto& rhs)
{
	return lhs.mod() < rhs.mod();
}

/**
 * @brief Programa de prueba de la clase punto.
 *
 * @details
 * Comprueba la construcción, la suma de puntos, la salida por flujo
 * y algunos operadores básicos.
 */
int main() {

	punto p1, p2;
	punto p3 = p1 + p2;

	// I/O
	p3.print(std::cout);
	std::cout << p3 << std::endl;


	// pruebas adicionales
	std::cout << std::boolalpha;
	std::cout << "!p1 = " << (!p1) << '\n';
	std::cout << "(p1 == p2) = " << (p1 == p2) << '\n';
	std::cout << "(p1 < p3) = " << (p1 < p3) << '\n';
}