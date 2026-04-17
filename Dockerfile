# Multi-stage build - Build stage
FROM mcr.microsoft.com/windows/servercore:ltsc2022 AS builder

# Set working directory
WORKDIR /build

# Copy source files
COPY . .

# Build the project using MSBuild
RUN cd /build && \
    powershell -Command \
    $env:Path += ';C:\Program Files\Microsoft Visual Studio\2022\BuildTools\VC\Tools\MSVC\14.39.33519\bin\Hostx64\x64' ; \
    msbuild LibraryManagementSystem.sln /p:Configuration=Release /p:Platform=x64 /m

# Runtime stage
FROM mcr.microsoft.com/windows/servercore:ltsc2022

WORKDIR /app

# Copy built executable from builder
COPY --from=builder /build/x64/Release/LibraryManagementSystem.exe .
COPY --from=builder /build/*.db .

# Create data directory for database
RUN mkdir /app/data

# Expose port (informational)
EXPOSE 5000

# Set environment variables
ENV DATABASE_PATH=C:\app\LibraryManagement.db

# Run the application
ENTRYPOINT ["LibraryManagementSystem.exe"]

