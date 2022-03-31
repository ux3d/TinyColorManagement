#ifndef LIGHT_H_
#define LIGHT_H_

// Luminous flux (Lichtstrom)
// Symbol:	Φ
// Unit:	lm (Lumen)
// https://en.wikipedia.org/wiki/Luminous_flux
// https://de.wikipedia.org/wiki/Lichtstrom

// Steradian (Steradiant)
// Symbol:	Ω
// Unit:	sr (steradian)
// https://en.wikipedia.org/wiki/Steradian
// https://de.wikipedia.org/wiki/Steradiant

// Luminous intensity (Lichtstaerke)
// Symbol:	I
// Unit:	cd (Candela) = lm / sr
// https://en.wikipedia.org/wiki/Luminous_intensity
// https://de.wikipedia.org/wiki/Lichtst%C3%A4rke_(Photometrie)

// Formula:	I = Φ / Ω
//
// Ω in all directions 4*π
// Formula:	I = Φ / 4*π

// Illuminance (Beleuchtungsstaerke)
// Symbol:	E
// Unit:	lux
// https://en.wikipedia.org/wiki/Illuminance
// https://de.wikipedia.org/wiki/Beleuchtungsst%C3%A4rke

// Formula:	E = I / d²			d is the distance in meters

// Luminance (Leuchtdichte)
// Symbol:	L
// Unit:	cd / m² (candela per square meter) = nits
// https://en.wikipedia.org/wiki/Luminance
// https://de.wikipedia.org/wiki/Leuchtdichte

// BRDF
// https://en.wikipedia.org/wiki/Bidirectional_reflectance_distribution_function
// https://de.wikipedia.org/wiki/Bidirektionale_Reflexionsverteilungsfunktion

// Formula:	L = f(v, l) * E					v is viewer and l is light
// Formula:	L = f(v, l) * E⊥ * dot(n, l)	n is the normal

// Directional light
// Formula:	L = f(v, l) * E⊥ * dot(n, l)

// Point light
// Formula:	L = f(v, l) * Φ/(4*π*d²) * dot(n, l)

// Spot light
// Formula:	L = f(v, l) * Φ/(π*d²) * dot(n, l) * angleAttenuation()

// Image based light
// Formula:	L = f(v, l) * Li * dot(n, l)

#endif /* LIGHT_H_ */
