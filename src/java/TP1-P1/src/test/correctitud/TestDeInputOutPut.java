/*
 * Creation : 03/09/2014
 */
package test.correctitud;

import java.io.BufferedWriter;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.io.Writer;
import java.util.Date;
import java.util.Random;

import main.Main;
import modelo.Puente;
import servicio.Saltarin;

public class TestDeInputOutPut {

	private static int PUENTEMAX = 1000;

	private static Random random = new Random(new Date().getTime());

	public static void main(String[] args) throws IOException {
		testGeneradorRandomOutPut();
		System.out.println("Test finalizaron de manera correcta!");
	}

	// Lo que vamos a hacer con este test es generarnos independientemente el
	// input del main de una instancia de puente.
	// Luego vamos a correr el algoritmo por separado y ver que el output del
	// programa es el mismo que el output del algoritmo
	public static void testGeneradorRandomOutPut() throws IOException {
		int casos = 100;
		StringBuilder archivoBuilder = new StringBuilder();
		StringBuilder solBuilder = new StringBuilder();
		for (int i = 0; i < casos; i++) {
			int n = random.nextInt(PUENTEMAX) + 1;
			Puente puente = new Puente(random, n);
			int saltoMax = random.nextInt(PUENTEMAX);
			archivoBuilder.append(n + " " + saltoMax);
			for (int j = 1; j <= n; j++) {
				archivoBuilder.append(puente.estaRoto(j) ? " 1" : " 0");
			}
			archivoBuilder.append("\n");
			solBuilder.append(Saltarin.saltarConOutPut(puente, saltoMax));
			solBuilder.append("\n");
		}
		archivoBuilder.append("0");
		Writer writer = null;
		try {
			writer = new BufferedWriter(new OutputStreamWriter(
					new FileOutputStream("test.txt"), "utf-8"));
			writer.write(archivoBuilder.toString());
		} catch (IOException ex) {
		} finally {
			try {
				writer.close();
			} catch (Exception ex) {
			}
		}
		String solMain = Main.runAlgo("test.txt");
		assert (solBuilder.toString().equals(solMain));

	}
}
