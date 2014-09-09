/*
 * Creation : 02/09/2014
 */
package test.correctitud;

import java.util.Date;
import java.util.Random;

import modelo.Puente;
import servicio.Saltarin;

/**
 * The Class TestCasoBordes.
 */
public class TestCasoBordes {

	/** The random. */
	private static Random random = new Random(new Date().getTime());

	/** The tamaniomax. */
	static int TAMANIOMAX = 1000;

	/**
	 * The main method.
	 * 
	 * @param args
	 *            the arguments
	 */
	// para correr este main hay que activar la opcion -ea en la VM.
	public static void main(String[] args) {
		TestConPuenteConTamanio0();
		TestConSaltoMaximo0();
		TestConSaltoMaximoMayorAPuente();
		testConPuenteNegativo();
		testConSaltoNegativo();
		System.out.println("Test finalizaron de manera correcta!");
	}

	/**
	 * Test con puente con tamanio0.
	 */
	private static void TestConPuenteConTamanio0() {
		Puente puente = new Puente(random, 0);
		assert (0 == Saltarin.saltar(puente, random.nextInt()));
		assert ("no".equals(Saltarin.saltarConOutPut(puente, random.nextInt())));
	}

	/**
	 * Test con salto maximo0.
	 */
	private static void TestConSaltoMaximo0() {
		Puente puente = new Puente(random, random.nextInt(TAMANIOMAX));
		assert (0 == Saltarin.saltar(puente, 0));
		String[] values = Saltarin.saltarConOutPut(puente, 0).split(" ");
		assert ("no".equals(values[0]));
	}

	/**
	 * Test con salto maximo mayor a puente.
	 */
	private static void TestConSaltoMaximoMayorAPuente() {
		Puente puente = new Puente(random, random.nextInt(TAMANIOMAX));
		int salto = puente.largo() + random.nextInt(TAMANIOMAX) + 1;
		assert (1 == Saltarin.saltar(puente, salto));

		String[] values = Saltarin.saltarConOutPut(puente, salto).split(" ");
		assert ("1".equals(values[0]));
		assert (String.valueOf(salto).equals(values[1]));
	}

	/**
	 * Test con puente negativo.
	 */
	private static void testConPuenteNegativo() {
		Puente puente = new Puente(random, -1);
		assert (0 == Saltarin.saltar(puente, random.nextInt()));
		String[] values = Saltarin.saltarConOutPut(puente, random.nextInt())
				.split(" ");
		assert ("no".equals(values[0]));
	}

	/**
	 * Test con salto negativo.
	 */
	private static void testConSaltoNegativo() {
		Puente puente = new Puente(random, random.nextInt(TAMANIOMAX));
		assert (0 == Saltarin.saltar(puente, -1));
		String[] values = Saltarin.saltarConOutPut(puente, -1).split(" ");
		assert ("no".equals(values[0]));
	}

}
