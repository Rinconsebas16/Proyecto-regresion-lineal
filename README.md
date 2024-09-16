Análisis del Mercado Inmobiliario mediante Regresión Lineal Simple
El objetivo principal del proyecto es analizar la correlación entre la "superficie cubierta" de una propiedad y su "precio", y luego construir un modelo de regresión lineal simple para predecir el precio de una propiedad dado su tamaño.
Las funcionalidades principales del proyecto incluyen:
- Lectura de datos desde un archivo CSV.
- Visualización de los datos en formato tabular.
- Análisis exploratorio de datos incluyendo el cálculo de la correlación entre variables.
- Construcción de un modelo de regresión lineal simple basado en la superficie cubierta y el precio de las propiedades.
- Evaluación del modelo usando métricas como el error cuadrático medio (MSE) y el coeficiente de determinación (R²).
- División de datos en conjuntos de entrenamiento y prueba para validar el modelo.


Para compilar el codigo se necesita un compilador de c++ o cualquier programa que pueda compilar codigo en c++
para compilarlo puedes copiar el codigo en tu compilador o clonar el repositorio en tu maquina local
Una vez clonado, cambia al directorio del repositorio:

cd Proyecto-regresion-lineal
para compilarl el codigo asegúrate de que el archivo main.cpp está presente en la carpeta src/ o en la raíz del proyecto, y que el archivo CSV está ubicado en la carpeta correcta.
Si estás usando g++ como compilador, puedes ejecutar el siguiente comando para compilar el código:
g++ -o regresion src/main.cpp
Esto generará un ejecutable llamado regresion en el directorio actual
Una vez que el código esté compilado correctamente, puedes ejecutar el programa con el siguiente comando:
./regresion


Como resultado 
nuestro codigo mostró que existe una correlación significativa entre la superficie cubierta de una propiedad y su precio
Los coeficientes obtenidos fueron:
b0: Valor de la intersección.
b1: Pendiente 
Error Cuadrático Medio (MSE):  indica que el error promedio entre los precios predichos y los precios reales es bajo
Coeficiente de Determinación (R²):  muestra qué tan bien el modelo explica la variabilidad de los precios en función de la superficie cubierta.
Coeficiente de Determinación (R²):  muestra qué tan bien el modelo explica la variabilidad de los precios en función de la superficie cubierta.
