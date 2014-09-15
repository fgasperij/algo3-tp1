/*
 * Creation : 03/09/2014
 */
package test.correctitud;

import java.util.Date;
import java.util.Random;

import modelo.Puente;
import servicio.Saltarin;

public class TestGeneradorDeCasos {

	private static int PUENTEMAX = 1000;

	private static Random random = new Random(new Date().getTime());

	// para correr este main hay que activar la opcion -ea en la VM.
	public static void main(String[] args) {
		testGeneradorRandom();
		System.out.println("Test finalizaron de manera correcta!");
	}

	// va a generar m casos, de puentes de tamaño maximo PUENTEMAX+1.
	// si no tiene solucion chequea que efectivamente no la tenga, y sino
	// chequea que todos los tablones esten bien
	public static void testGeneradorRandom() {
		int casos = 1000;
		for (int i = 0; i < casos; i++) {
			Puente puente = new Puente(random, random.nextInt(PUENTEMAX) + 1);
			int saltoMax = random.nextInt(PUENTEMAX);
			String[] sol = Saltarin.saltarConOutPut(puente, saltoMax)
					.split(" ");
			if (sol[0].equals("no")) {
				assert (contieneIntervaloDeTablonesMayorAsaltoMax(puente,
						saltoMax));
			} else {
				assert (1 <= Integer.valueOf(sol[0]));
				for (int k = 1; k < sol.length; k++) {
					int salto = Integer.valueOf(sol[k]);
					assert (!puente.estaRoto(salto));
				}
			}
		}

	}

	// Vamos a aprovecharnos de la propiedad de que si un puente no es posible
	// pasarlo, entonces contiene un intervalo de tablones rotos mayor o igual
	// al salto maximo
	private static boolean contieneIntervaloDeTablonesMayorAsaltoMax(
			Puente puente, int saltoMax) {
		boolean contiene = false;
		int i = 1;
		int contador = 0;
		while (i <= puente.largo() && !contiene) {
			if (puente.estaRoto(i)) {
				contador++;
			} else {
				contador = 0;
			}
			i++;
			contiene = contador >= saltoMax;
		}
		return contiene;
	}
}
