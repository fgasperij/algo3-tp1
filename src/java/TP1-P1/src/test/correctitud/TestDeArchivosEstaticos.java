package test.correctitud;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

import main.Main;

//Con este test vamos a tratar de testear con soluciones estaticas ya 
//probadas desde lo teorico.
//Las soluciones se van a encontrar en el arhcivo de solucion-estatic, y los
//puentes en el archivo de puentes-estatico
public class TestDeArchivosEstaticos {

	public static void main(String[] args) throws IOException {
		testEstatico();
		System.out.println("Test finalizaron de manera correcta!");
	}

	public static void testEstatico() throws IOException {
		String sol = Main.runAlgo("puentes-estatico");
		String solEstatica = readSolEstatica();
		assert (sol.equals(solEstatica));
	}

	public static String readSolEstatica() throws IOException {
		BufferedReader br = null;
		StringBuilder builder = new StringBuilder();
		try {
			br = new BufferedReader(new FileReader("solucion-estatica"));
			String line;
			line = br.readLine();
			while (line != null) {
				builder.append(line);
				builder.append("\n");
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
