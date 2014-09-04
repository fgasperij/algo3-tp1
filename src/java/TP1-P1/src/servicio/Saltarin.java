package servicio;

import modelo.Puente;

/**
 * The Class Saltarin.
 */
public class Saltarin {

	/**
	 * Saltar.
	 * 
	 * @param puente
	 *            the puente
	 * @param saltoMax
	 *            the salto max
	 * @return the int
	 */
	public static int saltar(Puente puente, int saltoMax) {
		// El codigo va a agarrar siempre el maximo salto, mientras pueda
		// saltar.
		int saltos = 0;
		if (saltoMax > 0) {
			int pos = 0;
			while (pos < puente.largo()) {
				int i = saltoMax;
				boolean salte = false;
				while (i > 0 && !salte) {
					if (puente.estaRoto(i + pos)) {
						i--;
					} else {
						pos += i;
						saltos++;
						salte = true;
					}
				}
				if (!salte) {
					return -1;
				}
			}
		}
		return saltos;
	}

	/**
	 * Saltar con out put.
	 * 
	 * @param puente
	 *            the puente
	 * @param saltoMax
	 *            the salto max
	 */
	public static String saltarConOutPut(Puente puente, int saltoMax) {
		// es el mismo codigo de arriba, solo que le agrego un builder, para que
		// me devuelva el string que necesito
		int saltos = 0;
		StringBuilder builder = new StringBuilder();
		if (saltoMax > 0) {
			int pos = 0;
			while (pos < puente.largo() + 1) {
				int i = saltoMax;
				boolean salte = false;
				while (i > 0 && !salte) {
					if (puente.estaRoto(i + pos)) {
						i--;
					} else {
						pos += i;
						builder.append(" " + pos);
						saltos++;
						salte = true;
						i = saltoMax;
					}
				}
				if (!salte) {
					return "no";
				}
			}
		}
		if (saltos != 0) {
			return saltos + builder.toString();
		}
		return "no";
	}
}
