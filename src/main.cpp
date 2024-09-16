#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <numeric>
#include <cmath>
#include <algorithm>
#include <random>

using namespace std;

struct Propiedad {
    string start_date;
    string end_date;
    string created_on;
    double lat;
    double lon;
    string l1;
    string l2;
    string l3;
    int rooms;
    int bedrooms;
    int bathrooms;
    double surface_total;
    double surface_covered;
    double price;
    string currency;
    string title;
    string description;
    string property_type;
    string operation_type;
};

double safeStod(const string& str) {
    try {
        return stod(str);
    } catch (const invalid_argument& e) {
        return 0.0;
    }
}

int safeStoi(const string& str) {
    try {
        return stoi(str);
    } catch (const invalid_argument& e) {
        return 0;
    }
}

vector<Propiedad> leerCSV(const string& nombreArchivo) {
    vector<Propiedad> propiedades;
    ifstream archivo(nombreArchivo);
    string linea;

    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo." << endl;
        return propiedades;
    }

    // Leer encabezados
    getline(archivo, linea);

    // Leer cada línea del archivo CSV
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        Propiedad propiedad;
        string temp;

        getline(ss, propiedad.start_date, ',');
        getline(ss, propiedad.end_date, ',');
        getline(ss, propiedad.created_on, ',');

        getline(ss, temp, ',');
        propiedad.lat = safeStod(temp);

        getline(ss, temp, ',');
        propiedad.lon = safeStod(temp);

        getline(ss, propiedad.l1, ',');
        getline(ss, propiedad.l2, ',');
        getline(ss, propiedad.l3, ',');

        getline(ss, temp, ',');
        propiedad.rooms = safeStoi(temp);

        getline(ss, temp, ',');
        propiedad.bedrooms = safeStoi(temp);

        getline(ss, temp, ',');
        propiedad.bathrooms = safeStoi(temp);

        getline(ss, temp, ',');
        propiedad.surface_total = safeStod(temp);

        getline(ss, temp, ',');
        propiedad.surface_covered = safeStod(temp);

        getline(ss, temp, ',');
        propiedad.price = safeStod(temp);

        getline(ss, propiedad.currency, ',');
        getline(ss, propiedad.title, ',');
        getline(ss, propiedad.description, ',');
        getline(ss, propiedad.property_type, ',');
        getline(ss, propiedad.operation_type, ',');
        propiedades.push_back(propiedad);
    }

    archivo.close();
    return propiedades;
}

void mostrarTabla(const vector<Propiedad>& propiedades) {
    // Imprimir encabezados incluyendo las nuevas columnas que solicitaste
    cout << left << setw(25) << "Location 3"
         << setw(10) << "Rooms"
         << setw(10) << "Bedrooms"
         << setw(10) << "Bathrooms"
         << setw(15) << "Surface Total"
         << setw(15) << "Surface Covered"
         << setw(20) << "Property Type"
         << setw(20) << "price"
         << endl;

    // Línea separadora
    cout << string(245, '-') << endl;

    // Imprimir cada propiedad con las nuevas columnas
    for (const auto& propiedad : propiedades) {
        cout << left << setw(20) << propiedad.start_date
             << setw(25) << propiedad.l3
             << setw(10) << propiedad.rooms
             << setw(10) << propiedad.bedrooms
             << setw(10) << propiedad.bathrooms
             << setw(15) << propiedad.surface_total
             << setw(15) << propiedad.surface_covered
             << setw(20) << propiedad.property_type
             << setw(20) << propiedad.price
             << endl;
    }
}

// Cálculo de la media
double calcularMedia(const vector<double>& datos) {
    double suma = accumulate(datos.begin(), datos.end(), 0.0);
    return suma / datos.size();
}

// Cálculo de la correlación
double calcularCorrelacion(const vector<double>& x, const vector<double>& y) {
    double media_x = calcularMedia(x);
    double media_y = calcularMedia(y);

    double numerador = 0.0;
    double denominador_x = 0.0;
    double denominador_y = 0.0;

    for (size_t i = 0; i < x.size(); i++) {
        numerador += (x[i] - media_x) * (y[i] - media_y);
        denominador_x += pow(x[i] - media_x, 2);
        denominador_y += pow(y[i] - media_y, 2);
    }

    return numerador / sqrt(denominador_x * denominador_y);
}

// Cálculo de los coeficientes de la regresión lineal
pair<double, double> calcularCoeficientesRegresion(const vector<double>& x, const vector<double>& y) {
    double media_x = calcularMedia(x);
    double media_y = calcularMedia(y);

    double numerador = 0.0;
    double denominador = 0.0;

    for (size_t i = 0; i < x.size(); i++) {
        numerador += (x[i] - media_x) * (y[i] - media_y);
        denominador += pow(x[i] - media_x, 2);
    }

    double b1 = numerador / denominador;
    double b0 = media_y - b1 * media_x;

    return make_pair(b0, b1);
}

// Cálculo del MSE
double calcularMSE(const vector<double>& y, const vector<double>& y_pred) {
    double suma = 0.0;
    for (size_t i = 0; i < y.size(); i++) {
        suma += pow(y[i] - y_pred[i], 2);
    }
    return suma / y.size();
}

// Cálculo del R²
double calcularR2(const vector<double>& y, const vector<double>& y_pred) {
    double media_y = calcularMedia(y);
    double ss_total = 0.0;
    double ss_res = 0.0;

    for (size_t i = 0; i < y.size(); i++) {
        ss_total += pow(y[i] - media_y, 2);
        ss_res += pow(y[i] - y_pred[i], 2);
    }

    return 1 - (ss_res / ss_total);
}

// Exportar datos para visualización
void exportarDatos(const vector<double>& x, const vector<double>& y, const string& nombreArchivo) {
    ofstream archivo(nombreArchivo);
    archivo << "Superficie Cubierta,Precio" << endl;
    for (size_t i = 0; i < x.size(); i++) {
        archivo << x[i] << "," << y[i] << endl;
    }
    archivo.close();
}

// Función para dividir los datos en conjuntos de entrenamiento y prueba
void dividirDatos(const vector<double>& x, const vector<double>& y, vector<double>& x_train, vector<double>& y_train, vector<double>& x_test, vector<double>& y_test, double test_size = 0.2) {
    vector<size_t> indices(x.size());
    iota(indices.begin(), indices.end(), 0); // Llenar con índices 0, 1, ..., x.size()-1

    // Barajar los índices
    random_device rd;
    mt19937 g(rd());
    shuffle(indices.begin(), indices.end(), g);

    size_t test_set_size = static_cast<size_t>(x.size() * test_size);

    // Dividir en conjuntos de entrenamiento y prueba
    for (size_t i = 0; i < x.size(); i++) {
        if (i < test_set_size) {
            x_test.push_back(x[indices[i]]);
            y_test.push_back(y[indices[i]]);
        } else {
            x_train.push_back(x[indices[i]]);
            y_train.push_back(y[indices[i]]);
        }
    }
}

// Función para evaluar el modelo en el conjunto de prueba
void evaluarModelo(const vector<double>& x_train, const vector<double>& y_train, const vector<double>& x_test, const vector<double>& y_test) {
    // Entrenar el modelo
    auto [b0, b1] = calcularCoeficientesRegresion(x_train, y_train);

    // Hacer predicciones en el conjunto de prueba
    vector<double> y_pred;
    for (double x : x_test) {
        y_pred.push_back(b0 + b1 * x);
    }

    // Evaluar el modelo
    double mse = calcularMSE(y_test, y_pred);
    double r2 = calcularR2(y_test, y_pred);
    cout << "Evaluación del Modelo en el Conjunto de Prueba:" << endl;
    cout << "MSE: " << mse << endl;
    cout << "R²: " << r2 << endl;
}

int main() {
    string nombreArchivo = "DS_Proyecto_01_Datos_Properati.csv";
    vector<Propiedad> propiedades = leerCSV(nombreArchivo);

    // Mostrar los datos en forma de tabla
    mostrarTabla(propiedades);

    // Análisis Exploratorio de Datos
    vector<double> precios;
    vector<double> superficies_cubiertas;

    for (const auto& propiedad : propiedades) {
        if (propiedad.price > 0 && propiedad.surface_covered > 0) { // Filtrar datos válidos
            precios.push_back(propiedad.price);
            superficies_cubiertas.push_back(propiedad.surface_covered);
        }
    }

    double correlacion = calcularCorrelacion(superficies_cubiertas, precios);
    cout << "\nCorrelación entre superficie cubierta y precio: " << correlacion << endl;

    // Regresión Lineal Simple
    auto [b0, b1] = calcularCoeficientesRegresion(superficies_cubiertas, precios);
    cout << "Modelo de Regresión Lineal: Precio = " << b0 << " + " << b1 << " * Superficie Cubierta" << endl;

    // Predicciones
    vector<double> precios_predichos;
    for (double superficie : superficies_cubiertas) {
        precios_predichos.push_back(b0 + b1 * superficie);
    }

    double mse = calcularMSE(precios, precios_predichos);
    double r2 = calcularR2(precios, precios_predichos);
    cout << "MSE: " << mse << endl;
    cout << "R²: " << r2 << endl;

    // Exportar datos para visualización
    exportarDatos(superficies_cubiertas, precios, "datos_visualizacion_superficie_cubierta.csv");

    // Validación del Modelo
    vector<double> x_train, y_train, x_test, y_test;
    dividirDatos(superficies_cubiertas, precios, x_train, y_train, x_test, y_test);
    evaluarModelo(x_train, y_train, x_test, y_test);

    return 0;
}