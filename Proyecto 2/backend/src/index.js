const app = require('./app');
require('dotenv').config(); // npm install dotenv || dotenv sirve para poder leer las variables de entorno

const PORT = process.env.PORT || 3001; // process.env.PORT es una variable de entorno que se puede configurar en el archivo .env, sino se configura se usara el puerto 3000

app.listen(PORT, () => {
    console.log(`Server running on port ${PORT}`);
});