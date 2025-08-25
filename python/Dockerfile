FROM python:3.13-alpine

WORKDIR /app

# Install build dependencies for native extensions
RUN apk add --no-cache gcc musl-dev

COPY requirements.txt .
RUN pip install --no-cache-dir -r requirements.txt

COPY . .

CMD ["python", "main.py"]
