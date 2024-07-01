# Ejecutar Mongosh con Docker

Para ejecutar Mongosh con Docker, puedes utilizar el siguiente comando:

```shell
docker exec -it mongodb mongosh
```

Aquí tienes una explicación de cada parte del comando:

- `docker exec`: Este comando te permite ejecutar un comando dentro de un contenedor de Docker en ejecución.
- `-it`: Estas banderas te permiten interactuar con el contenedor como si estuvieras frente a él. La bandera `-i` te permite enviar entrada al contenedor, y la bandera `-t` asigna un pseudo-TTY al contenedor.
- `mongodb`: Este es el nombre del contenedor de Docker en el que deseas ejecutar el comando. Puedes reemplazar esto con el nombre real de tu contenedor de MongoDB.
- `mongosh`: Este es el comando que deseas ejecutar dentro del contenedor. En este caso, es la consola de Mongosh.

Al ejecutar este comando, podrás acceder a la consola de Mongosh y ejecutar comandos de MongoDB dentro de tu contenedor de Docker.


# Comandos Básicos de MongoDB

## Autenticación

Antes de poder comenzar a usar MongoDB, primero debes autenticarte. Puedes hacer esto ejecutando el siguiente comando:

```shell
use admin
db.auth("tu_usuario", "tu_contraseña")
```

Reemplaza "tu_usuario" y "tu_contraseña" con tus credenciales reales de MongoDB.

## Comandos Básicos

### Agregar (Insertar)

Para agregar un nuevo documento a una colección, utiliza el método `insertOne()`:

```shell
db.collection.insertOne({ nombre: "Juan", edad: 30 })
```

### Seleccionar (Buscar)

Para recuperar documentos de una colección, utiliza el método `find()`:

```shell
db.collection.find()
```

También puedes especificar un filtro para recuperar documentos específicos:

```shell
db.collection.find({ nombre: "Juan" })
```

### Editar (Actualizar)

Para actualizar un documento en una colección, utiliza el método `updateOne()`:

```shell
db.collection.updateOne({ nombre: "Juan" }, { $set: { edad: 31 } })
```
### Eliminar

Para eliminar varios documentos de una colección, utiliza el método `deleteMany()`:

```shell
db.collection.deleteMany({ nombre: "Juan" })
```

Esto eliminará todos los documentos que coincidan con el filtro especificado. Puedes ajustar el filtro según tus necesidades.

Para eliminar un documento de una colección, utiliza el método `deleteOne()`:

```shell
db.collection.deleteOne({ nombre: "Juan" })
```

### Contar

Para contar el número de documentos en una colección, utiliza el método `count()`:

```shell
db.collection.count()
```

### Ordenar

Para ordenar los documentos en una colección, utiliza el método `sort()`:

```shell
db.collection.find().sort({ nombre: 1 })
```

El número 1 indica orden ascendente, mientras que -1 indica orden descendente.

### Limitar

Para limitar el número de documentos recuperados de una colección, utiliza el método `limit()`:

```shell
db.collection.find().limit(5)
```

Esto devolverá solo los primeros 5 documentos de la colección.

### Saltar

Para saltar un número específico de documentos en una colección, utiliza el método `skip()`:

```shell
db.collection.find().skip(10)
```

Esto omitirá los primeros 10 documentos y devolverá los siguientes.

## Salir de Mongosh

Para salir de la consola de Mongosh, simplemente escribe:

```shell
exit
```

o presiona Ctrl+D (en Linux/macOS) o Ctrl+Z (en Windows).

