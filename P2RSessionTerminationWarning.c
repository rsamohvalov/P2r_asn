/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "P2r"
 * 	found in "P2r.asn1"
 */

#include "P2RSessionTerminationWarning.h"

static int
memb_warning_id_constraint_1(const asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	long value;
	
	if(!sptr) {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	value = *(const long *)sptr;
	
	if((value >= 0 && value <= 65535)) {
		/* Constraint check succeeded */
		return 0;
	} else {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

static int
memb_estimated_time_constraint_1(const asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	long value;
	
	if(!sptr) {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	value = *(const long *)sptr;
	
	if((value >= 0 && value <= 255)) {
		/* Constraint check succeeded */
		return 0;
	} else {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

static asn_oer_constraints_t asn_OER_memb_warning_id_constr_2 CC_NOTUSED = {
	{ 2, 1 }	/* (0..65535) */,
	-1};
static asn_per_constraints_t asn_PER_memb_warning_id_constr_2 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 16,  16,  0,  65535 }	/* (0..65535) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_memb_estimated_time_constr_4 CC_NOTUSED = {
	{ 1, 1 }	/* (0..255) */,
	-1};
static asn_per_constraints_t asn_PER_memb_estimated_time_constr_4 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 8,  8,  0,  255 }	/* (0..255) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
asn_TYPE_member_t asn_MBR_P2RSessionTerminationWarning_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct P2RSessionTerminationWarning, warning_id),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NativeInteger,
		0,
		{ &asn_OER_memb_warning_id_constr_2, &asn_PER_memb_warning_id_constr_2,  memb_warning_id_constraint_1 },
		0, 0, /* No default value */
		"warning-id"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct P2RSessionTerminationWarning, reason),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_Reason,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"reason"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct P2RSessionTerminationWarning, estimated_time),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NativeInteger,
		0,
		{ &asn_OER_memb_estimated_time_constr_4, &asn_PER_memb_estimated_time_constr_4,  memb_estimated_time_constraint_1 },
		0, 0, /* No default value */
		"estimated-time"
		},
};
static const ber_tlv_tag_t asn_DEF_P2RSessionTerminationWarning_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_P2RSessionTerminationWarning_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* warning-id */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* reason */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 } /* estimated-time */
};
asn_SEQUENCE_specifics_t asn_SPC_P2RSessionTerminationWarning_specs_1 = {
	sizeof(struct P2RSessionTerminationWarning),
	offsetof(struct P2RSessionTerminationWarning, _asn_ctx),
	asn_MAP_P2RSessionTerminationWarning_tag2el_1,
	3,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	3,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_P2RSessionTerminationWarning = {
	"P2RSessionTerminationWarning",
	"P2RSessionTerminationWarning",
	&asn_OP_SEQUENCE,
	asn_DEF_P2RSessionTerminationWarning_tags_1,
	sizeof(asn_DEF_P2RSessionTerminationWarning_tags_1)
		/sizeof(asn_DEF_P2RSessionTerminationWarning_tags_1[0]), /* 1 */
	asn_DEF_P2RSessionTerminationWarning_tags_1,	/* Same as above */
	sizeof(asn_DEF_P2RSessionTerminationWarning_tags_1)
		/sizeof(asn_DEF_P2RSessionTerminationWarning_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_P2RSessionTerminationWarning_1,
	3,	/* Elements count */
	&asn_SPC_P2RSessionTerminationWarning_specs_1	/* Additional specs */
};

