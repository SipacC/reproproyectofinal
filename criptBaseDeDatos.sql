--se cre la tabla para los usuarios
CREATE TABLE Usuario (
    id_usuario SERIAL PRIMARY KEY,
    Nombre VARCHAR(100) NOT NULL,
    Correo VARCHAR(100) UNIQUE NOT NULL,
    Tipo VARCHAR(20) CHECK (Tipo IN ('lector', 'gestor')),
    Contrasena VARCHAR(255) NOT NULL
);

-- secrea la tabla para los libros
CREATE TABLE Libro (
    ISBN VARCHAR PRIMARY KEY,
    Titulo VARCHAR(150) NOT NULL,
    Autor VARCHAR(100),
    Editorial VARCHAR(100),
    Anio_publicacion INT,
    Materia VARCHAR(100),
    Estado VARCHAR(20) DEFAULT 'disponible' CHECK (Estado IN ('disponible', 'prestado')),
    ejemplares INT DEFAULT 0 CHECK (ejemplares >= 0)
);

-- se crea la tabla para los prestamos
CREATE TABLE Prestamo (
    id_prestamo SERIAL PRIMARY KEY,
    id_usuario INT NOT NULL REFERENCES Usuario(id_usuario) ON DELETE CASCADE,
    isbn_libro VARCHAR NOT NULL REFERENCES Libro(ISBN) ON DELETE CASCADE,
    Fecha_prestamo DATE NOT NULL,
    Fecha_devolucion DATE,
    Estado VARCHAR(20) DEFAULT 'activo' CHECK (Estado IN ('activo', 'devuelto')),
    UNIQUE(id_usuario, isbn_libro, Fecha_prestamo)
);

-- se crea la tabla para las solicitudes para prestar los libros
CREATE TABLE Solicitud (
    id_solicitud SERIAL PRIMARY KEY,
    id_usuario INT REFERENCES Usuario(id_usuario) ON DELETE CASCADE,
    isbn_libro VARCHAR REFERENCES Libro(ISBN) ON DELETE CASCADE,
    tipo VARCHAR(20) CHECK (tipo IN ('prestamo', 'devolucion')),
    estado VARCHAR(20) DEFAULT 'pendiente' CHECK (estado IN ('pendiente', 'aceptada', 'rechazada')),
    fecha_solicitud TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);
