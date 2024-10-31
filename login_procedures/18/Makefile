ALLCPP=login.cpp login.cpp
SOURCES=$(filter-out authlib.cpp,$(ALLCPP))
TARGETS=$(patsubst %.cpp,%,$(SOURCES))
CPPFLAGS=-Wall -pedantic -Wextra -std=c++11 -Wno-deprecated-declarations
OPENSSL_FLAGS=-Iusr/include/openssl 
LDFLAGS=-Lusr/include/openssl -lssl -lcrypto
C=g++

all: $(TARGETS)

authlib.o: authlib.cpp
	$(C) $(CPPFLAGS) -c $< -o $@ 

login-tmp.cpp: login.cpp
	openssl enc -d -aes-256-cbc -pbkdf2 -in $< -out $@ -pass pass:SECRET_PASSWORD

login.o: login-tmp.cpp
	$(C) $(CPPFLAGS) $(OPENSSL_FLAGS) -c $< -o $@ 
	rm -f $<

login: login.o authlib.o
	$(C) $(CPPFLAGS) $^ $(LDFLAGS) -o $@

clean:
	rm -f $(TARGETS) *.o
	rm -f login-tmp.cpp login.o 2>/dev/null || true

.PHONY: all clean
