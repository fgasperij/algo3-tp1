package test.complejidad;

import java.util.Date;
import java.util.Random;

import modelo.Puente;
import servicio.Saltarin;

/**
 * The Class TestDeTamanioFijo.
 */
public class TestDeTamanioFijo {

	private static int PUENTEMAX = 500000000;

	private static Random random = new Random(new Date().getTime());

	private static int SALTOMAX = 10;

	private static int CANTIDADDEIERACIONES = 100;

	/**
	 * The main method.
	 * 
	 * @param args
	 *            the arguments
	 */

	// Este metodo lo utilizamos para medir tiempos, notamos que a partir de los
	// 500000000 elementos la entrada comienza a tener un diferencia de tiempo
	// (tF-tI) significante
	// El primer valor es el N, el segundo una constante k la cual hace que se
	// resuelven k puentes de tamaño N. El algoritmo de me devuelve el promedio
	// de solucion de esos puentes.
	// Luego hay una tercer constante m que es el tamanio del saltoMax, la
	// implementacion genera un saltoMax aleatorio, pero que no puede ser mayor
	// a m.
	// Vamos a generar casos que tengan N >> saltoMax, ya que en esos casos se
	// ve mas clara la complejidad.
	public static void main(String[] args) {
		testDeComplejidad();
	}

	public static void testDeComplejidad() {
		for (int i = 1; i < PUENTEMAX; i += 50000) {
			float prom = 0;
			for (int j = 0; j < CANTIDADDEIERACIONES; j++) {
				int saltoMax = random.nextInt(SALTOMAX);
				Long ats = new Date().getTime();
				Puente puente = new Puente(random, i);
				Saltarin.saltar(puente, saltoMax);
				Long dps = new Date().getTime();
				// Esto lo hacemos para evitar outlayers
				if (j > 10) {
					prom += dps - ats;
				}
			}
			System.out.println(i / 10000 + "," + prom
					/ (CANTIDADDEIERACIONES - 10));
		}
	}
}
