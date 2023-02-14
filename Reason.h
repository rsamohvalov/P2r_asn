/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "P2r"
 * 	found in "P2r.asn1"
 */

#ifndef	_Reason_H_
#define	_Reason_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeEnumerated.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum Reason {
	Reason_unknown	= 0,
	Reason_planned	= 1,
	Reason_unplanned	= 2
	/*
	 * Enumeration is extensible
	 */
} e_Reason;

/* Reason */
typedef long	 Reason_t;

/* Implementation */
extern asn_per_constraints_t asn_PER_type_Reason_constr_1;
extern asn_TYPE_descriptor_t asn_DEF_Reason;
extern const asn_INTEGER_specifics_t asn_SPC_Reason_specs_1;
asn_struct_free_f Reason_free;
asn_struct_print_f Reason_print;
asn_constr_check_f Reason_constraint;
ber_type_decoder_f Reason_decode_ber;
der_type_encoder_f Reason_encode_der;
xer_type_decoder_f Reason_decode_xer;
xer_type_encoder_f Reason_encode_xer;
oer_type_decoder_f Reason_decode_oer;
oer_type_encoder_f Reason_encode_oer;
per_type_decoder_f Reason_decode_uper;
per_type_encoder_f Reason_encode_uper;

#ifdef __cplusplus
}
#endif

#endif	/* _Reason_H_ */
#include <asn_internal.h>