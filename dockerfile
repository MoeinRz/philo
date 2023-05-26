# Base image
FROM gcc:latest

# Set the working directory inside the container
WORKDIR /app

# Copy the source code into the container
COPY src /app/src
COPY includes /app/includes
COPY Makefile /app/Makefile

# Build the project
RUN make

# Run the project when the container starts
CMD ["./philosophers", "4", "200", "100", "150"]

# Expose any necessary ports (if applicable)
# EXPOSE <port_number>
