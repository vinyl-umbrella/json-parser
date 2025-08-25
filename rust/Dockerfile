FROM rust:1.80-alpine AS builder

WORKDIR /app

# Install build dependencies
RUN apk add --no-cache musl-dev

# Copy only Cargo.toml first for better caching
COPY Cargo.toml ./

# Create a dummy main.rs to allow dependency resolution
RUN mkdir src && echo "fn main() {}" > src/main.rs

# Download dependencies
RUN cargo build --release --bin json-parser-test
RUN rm src/main.rs

# Copy actual source code
COPY src/ src/

# Build the actual application
RUN cargo build --release

FROM alpine:latest
RUN apk --no-cache add ca-certificates
WORKDIR /root/

COPY --from=builder /app/target/release/json-parser-test .

CMD ["./json-parser-test"]
