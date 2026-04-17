# Use official Windows Server Core image as base
FROM mcr.microsoft.com/windows/servercore:ltsc2022 as builder

# Install required tools
RUN powershell -Command \
    Invoke-WebRequest -Uri "https://aka.ms/vs/17/release/vs_buildtools.exe" -OutFile "vs_buildtools.exe" ; \
    .\vs_buildtools.exe --quiet --norestart --nocache \
    --installPath C:\BuildTools \
    --add Microsoft.VisualStudio.Workload.VCTools \
    --add Microsoft.VisualStudio.Component.VC.Tools.x86.x64

# Copy project files
WORKDIR /app
COPY . .

# Build the project
RUN powershell -Command \
    $env:Path += ';C:\BuildTools\VC\Tools\MSVC\14.30.30705\bin\Hostx64\x64' ; \
    msbuild LibraryManagementSystem.sln /p:Configuration=Release /p:Platform=x64

# Runtime stage
FROM mcr.microsoft.com/windows/servercore:ltsc2022

WORKDIR /app
COPY --from=builder /app/x64/Release/LibraryManagementSystem.exe .

# Expose port if needed
EXPOSE 5000

# Run the application
CMD ["LibraryManagementSystem.exe"]
