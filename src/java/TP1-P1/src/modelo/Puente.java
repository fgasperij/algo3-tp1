package modelo;

import java.util.Random;

/**
 * The Class Puente.
 */
public class Puente {

	/** The largo. */
	private int largo = 0;

	/**
	 * Instantiates a new puente.
	 * 
	 * @param random
	 *            the random
	 * @param i
	 *            the i
	 */
	public Puente(Random random, int i) {
		if (i > 0) {
			largo = i;
			tablones = new boolean[i];
			for (int j = 0; j < tablones.length; j++) {
				tablones[j] = random.nextBoolean();
			}
		}
	}

	/**
	 * Instantiates a new puente.
	 * 
	 * @param array
	 *            the array
	 */
	public Puente(boolean[] array) {
		if (array != null) {
			largo = array.length;
			tablones = new boolean[array.length];
			for (int j = 0; j < array.length; j++) {
				tablones[j] = array[j];
			}
		}
	}

	/** The tablones. */
	boolean[] tablones;

	/**
	 * Largo.
	 * 
	 * @return the int
	 */
	public int largo() {
		return largo;
	}

	/**
	 * Esta roto.
	 * 
	 * @param pos
	 *            the pos
	 * @return true, if successful
	 */
	public boolean estaRoto(int pos) {
		if (pos <= 0) {
			return true;
		} else if (pos > largo) {
			return false;
		} else {
			return tablones[pos - 1];
		}
	}

	@Override
	public String toString() {
		StringBuilder builder = new StringBuilder();
		builder.append(largo);
		for (int i = 0; i < largo; i++) {
			if (tablones[i]) {
				builder.append(" 1");
			} else {
				builder.append(" 0");
			}
		}
		return builder.toString();
	}
}
