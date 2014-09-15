/*
 * Creation : 02/09/2014
 */
package main;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

import modelo.Puente;
import servicio.Saltarin;

/**
 * The Class Main.
 */
public class Main {

	/**
	 * Main.
	 * 
	 * @param args
	 *            the args
	 * @throws IOException
	 *             Signals that an I/O exception has occurred.
	 */
	public static void main(String[] args) throws IOException {
		String file = args[0];
		String s = runAlgo(file);
		System.out.println(s);
	}

	public static String runAlgo(String file) throws IOException {
		BufferedReader br = null;
		StringBuilder builder = new StringBuilder();
		try {
			br = new BufferedReader(new FileReader(file));
			String line;
			line = br.readLine();
			while (line != null) {
				String[] values = line.split(" ");
				if (values.length > 1) {
					int n = Integer.valueOf(values[0]);
					int k = Integer.valueOf(values[1]);
					boolean[] array = new boolean[n];
					for (int i = 2, j = 0; i < values.length; i++, j++) {
						if (values[i].equals("0")) {
							array[j] = false;
						} else {
							array[j] = true;
						}
					}
					Puente puente = new Puente(array);
					builder.append(Saltarin.saltarConOutPut(puente, k) + "\n");
				}
				line = br.readLine();
			}
		} catch (FileNotFoundException e) {
			System.out.println("archivo no encontrado");
		} catch (IOException e) {
			System.out.println("error leyendo archivo");
			e.printStackTrace();
		} finally {
			if (br != null) {
				br.close();
			}
		}
		return builder.toString();
	}
}
