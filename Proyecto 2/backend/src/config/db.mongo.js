const { MongoClient } = require('mongodb');
require('dotenv').config();

const {
    MONGODB_USER,
    MONGODB_PASSWORD,
    MONGODB_HOST,
    MONGODB_PORT,
    MONGODB_DATABASE,
} = process.env;

const uri = `mongodb://${MONGODB_USER}:${MONGODB_PASSWORD}@${MONGODB_HOST}:${MONGODB_PORT}`;

const insertData = async (collec, data) => {
    console.log('URI: ', uri)
    const mongoClient = new MongoClient(uri);
    try {
        await mongoClient.connect().then(() => console.log('Conectado a la base de datos'));
        const dbmongo = mongoClient.db(MONGODB_DATABASE);
        const coleccion = dbmongo.collection(collec);
        const result = await coleccion.insertOne(data);
        return result;
    } catch (error) {
        console.error('Error insertData: ', error);
        return error;
    } finally {
        await mongoClient.close();
        console.log('Desconectado de la base de datos')
    }
};

module.exports = {
    insertData,
};