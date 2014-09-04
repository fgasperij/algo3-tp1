package test.complejidad;

import java.util.Date;
import java.util.Random;

import modelo.Puente;
import servicio.Saltarin;

// Este test lo vamos a utilizar para medir el tiempo que tarde en resolverse
// una entrada en el procesador. Para ello vamos a tratar de mediar una entrada resuelta
// k veces.
// El test va a ser similiar al de tamaño fijo pero corriendo cada instancia k veces.
public class TestDeEntradaAlProcesador {

	private static int PUENTEMAX = 500000000;

	private static Random random = new Random(new Date().getTime());

	private static int SALTOMAX = 10;

	private static int CANTIDADDECORRIDAS = 10;

	private static int CANTIDADDEIERACIONES = 10;

	public static void main(String[] args) {
		testEntradaAlProcesador();
	}

	public static void testEntradaAlProcesador() {
		for (int i = 500000; i < PUENTEMAX; i += 500000) {
			float prom = 0;
			for (int j = 0; j < CANTIDADDEIERACIONES; j++) {
				float promSubj = 0;
				int saltoMax = random.nextInt(SALTOMAX);
				boolean[] b = new boolean[i];
				for (int k = 0; k < b.length; k++) {
					b[k] = random.nextBoolean();
				}
				for (int k = 0; k < CANTIDADDECORRIDAS; k++) {
					Long ats = new Date().getTime();
					Puente puente = new Puente(b);
					Saltarin.saltar(puente, saltoMax);
					Long dps = new Date().getTime();
					promSubj += dps - ats;
				}
				prom += promSubj / (CANTIDADDECORRIDAS);

			}
			System.out.println(i / 100000 + "," + prom / CANTIDADDEIERACIONES);
		}
	}

}
