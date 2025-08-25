FROM ruby:3.2-alpine

WORKDIR /app

# Install build dependencies
RUN apk add --no-cache build-base

COPY Gemfile Gemfile.lock* ./
RUN bundle install

COPY . .

CMD ["ruby", "main.rb"]
