# Library Management System - Docker Setup

## Prerequisites

- Docker Desktop installed
- Windows 10/11 (for Windows containers)
- At least 4GB RAM allocated to Docker

## Build and Run

### Option 1: Using docker-compose (Recommended)

```bash
docker-compose up --build
```

### Option 2: Using Docker CLI

```bash
# Build image
docker build -t library-management:latest .

# Run container
docker run -it --name library-management library-management:latest
```

## Stopping the Container

```bash
# Using docker-compose
docker-compose down

# Using Docker CLI
docker stop library-management
docker rm library-management
```

## Viewing Logs

```bash
# Using docker-compose
docker-compose logs -f

# Using Docker CLI
docker logs -f library-management
```

## Testing Accounts

When the application starts, use these test accounts:

**Member Accounts:**
- Email: huy@email.com, Password: huy123
- Email: hung@email.com, Password: hung123
- Email: linh@email.com, Password: linh123

**Librarian Account:**
- Username: admin, Password: admin123

## Database

The database file (LibraryManagement.db) is stored in the `library-data` volume for persistence.

## Troubleshooting

If you encounter issues with Windows containers, ensure:
1. Docker is configured to use Windows containers
2. You have sufficient disk space
3. Hyper-V is enabled on Windows

## Notes

- This Dockerfile uses Windows Server Core as the base image
- For Linux deployment, create a separate Dockerfile using a Linux base image
- The application runs in console mode inside the container
