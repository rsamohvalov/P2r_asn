include Makefile.am.libasncodec

LIBS += -lm -lpthread
CFLAGS += $(ASN_MODULE_CFLAGS) -DASN_PDU_COLLECTION -I.
ASN_LIBRARY ?= libasncodec.a
P2R_LIBRARY ?= libP2r.a
ASN_PROGRAM ?= p2r-client-server-example
ASN_PROGRAM_SRCS ?= \
	p2r-client-server-example.c
	
P2R_SRCS ?= \
	P2rServer.c \
	P2rClient.c

all: $(ASN_PROGRAM)

$(ASN_PROGRAM): $(ASN_LIBRARY) $(P2R_LIBRARY) $(ASN_PROGRAM_SRCS:.c=.o)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $(ASN_PROGRAM) $(ASN_PROGRAM_SRCS:.c=.o) $(LDFLAGS) $(P2R_LIBRARY) $(ASN_LIBRARY) $(LIBS)

$(P2R_LIBRARY): $(P2R_SRCS:.c=.o)
	$(AR) rcs $@ $(P2R_SRCS:.c=.o)

$(ASN_LIBRARY): $(ASN_MODULE_SRCS:.c=.o)
	$(AR) rcs $@ $(ASN_MODULE_SRCS:.c=.o)

.SUFFIXES:
.SUFFIXES: .c .o

.c.o:
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f $(ASN_PROGRAM) $(ASN_LIBRARY) $(P2R_LIBRARY)
	rm -f $(ASN_MODULE_SRCS:.c=.o) $(ASN_PROGRAM_SRCS:.c=.o) $(P2R_LIBRARY:.c=.o)

regen: regenerate-from-asn1-source

regenerate-from-asn1-source:
	asn1c P2r.asn1

