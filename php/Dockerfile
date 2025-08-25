FROM php:8.2-cli-alpine

WORKDIR /app

# Install build dependencies for simdjson-php
RUN apk add --no-cache \
    build-base \
    autoconf \
    git

# Try to install simdjson-php (optional)
RUN pecl install simdjson || echo "simdjson installation failed, continuing without it"

COPY . .

CMD ["php", "main.php"]
