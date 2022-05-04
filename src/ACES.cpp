#include "ACES.h"

/*
=============================================================================
	ACES: Academy Color Encoding System
	https://github.com/ampas/aces-dev/tree/v1.0

	License Terms for Academy Color Encoding System Components

	Academy Color Encoding System (ACES) software and tools are provided by the Academy under
	the following terms and conditions: A worldwide, royalty-free, non-exclusive right to copy, modify, create
	derivatives, and use, in source and binary forms, is hereby granted, subject to acceptance of this license.

	Copyright © 2013 Academy of Motion Picture Arts and Sciences (A.M.P.A.S.). Portions contributed by
	others as indicated. All rights reserved.

	Performance of any of the aforementioned acts indicates acceptance to be bound by the following
	terms and conditions:

	 *	Copies of source code, in whole or in part, must retain the above copyright
		notice, this list of conditions and the Disclaimer of Warranty.
	 *	Use in binary form must retain the above copyright notice, this list of
		conditions and the Disclaimer of Warranty in the documentation and/or other
		materials provided with the distribution.
	 *	Nothing in this license shall be deemed to grant any rights to trademarks,
		copyrights, patents, trade secrets or any other intellectual property of
		A.M.P.A.S. or any contributors, except as expressly stated herein.
	 *	Neither the name "A.M.P.A.S." nor the name of any other contributors to this
		software may be used to endorse or promote products derivative of or based on
		this software without express prior written permission of A.M.P.A.S. or the
		contributors, as appropriate.

	This license shall be construed pursuant to the laws of the State of California,
	and any disputes related thereto shall be subject to the jurisdiction of the courts therein.

	Disclaimer of Warranty: THIS SOFTWARE IS PROVIDED BY A.M.P.A.S. AND CONTRIBUTORS "AS
	IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
	IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND
	NON-INFRINGEMENT ARE DISCLAIMED. IN NO EVENT SHALL A.M.P.A.S., OR ANY
	CONTRIBUTORS OR DISTRIBUTORS, BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
	SPECIAL, EXEMPLARY, RESITUTIONARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
	NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
	DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
	OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
	NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
	EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

	WITHOUT LIMITING THE GENERALITY OF THE FOREGOING, THE ACADEMY SPECIFICALLY
	DISCLAIMS ANY REPRESENTATIONS OR WARRANTIES WHATSOEVER RELATED TO PATENT OR
	OTHER INTELLECTUAL PROPERTY RIGHTS IN THE ACADEMY COLOR ENCODING SYSTEM, OR
	APPLICATIONS THEREOF, HELD BY PARTIES OTHER THAN A.M.P.A.S.,WHETHER DISCLOSED
	OR UNDISCLOSED.
=============================================================================
*/

glm::mat3 saturationMatrix(double sat, glm::vec3 Yrgb)
{
	// This function determines the terms for a 3x3 saturation matrix that is
	// based on the luminance of the input.

	glm::mat3 M;

	M[0][0] = (1.0 - sat) * Yrgb[0] + sat;
	M[1][0] = (1.0 - sat) * Yrgb[0];
	M[2][0] = (1.0 - sat) * Yrgb[0];

	M[0][1] = (1.0 - sat) * Yrgb[1];
	M[1][1] = (1.0 - sat) * Yrgb[1] + sat;
	M[2][1] = (1.0 - sat) * Yrgb[1];

	M[0][2] = (1.0 - sat) * Yrgb[2];
	M[1][2] = (1.0 - sat) * Yrgb[2];
	M[2][2] = (1.0 - sat) * Yrgb[2] + sat;

	M = glm::transpose(M);

	return M;
}

