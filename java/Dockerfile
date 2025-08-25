FROM amazoncorretto:17-alpine AS builder

WORKDIR /app

# Install Maven
RUN apk add --no-cache maven

COPY pom.xml .
RUN mvn dependency:go-offline

COPY . .
RUN mvn compile

FROM amazoncorretto:17-alpine
WORKDIR /app

# Install Maven for runtime execution
RUN apk add --no-cache maven

COPY --from=builder /app .

CMD ["mvn", "-q", "compile", "exec:java"]
