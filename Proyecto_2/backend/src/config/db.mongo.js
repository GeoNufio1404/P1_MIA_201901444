const { MongoClient } = require('mongodb');
require('dotenv').config();

const {
    MONGODB_USER,
    MONGODB_PASSWORD,
    MONGODB_HOST,
    MONGODB_PORT,
    MONGODB_DATABASE,
} = process.env;

const uri = `mongodb://${MONGODB_USER}:${MONGODB_PASSWORD}@${MONGODB_HOST}:${MONGODB_PORT}/${MONGODB_DATABASE}?authSource=admin`;

async function insertData(collec, data) {
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
    }
}

// Obtiene todos los datos de una colección y si se envia un objeto como segundo parametro, se filtra por los campos enviados
async function getCollection(collec, filter = {}) {
    const mongoClient = new MongoClient(uri);
    try {
        await mongoClient.connect().then(() => console.log('Conectado a la base de datos'));
        const dbmongo = mongoClient.db(MONGODB_DATABASE);
        const coleccion = dbmongo.collection(collec);
        const result = await coleccion.find(filter).toArray();
        return result;
    } catch (error) {
        console.error('Error getCollection: ', error);
        return error;
    } finally {
        await mongoClient.close();
    }
}


module.exports = {
    insertData,
    getCollection
};