FROM alpine:latest

# Install build tools and JSON libraries
RUN apk add --no-cache \
    gcc \
    musl-dev \
    make \
    pkgconfig \
    cjson-dev \
    jansson-dev \
    json-c-dev \
    git

# Install parson (not available as package, build from source)
RUN git clone https://github.com/kgabis/parson.git /tmp/parson && \
    cd /tmp/parson && \
    gcc -fPIC -shared -o libparson.so parson.c && \
    cp libparson.so /usr/lib/ && \
    cp parson.h /usr/include/ && \
    rm -rf /tmp/parson

WORKDIR /app

COPY . .

# Build the application
RUN make

CMD ["./test"]
