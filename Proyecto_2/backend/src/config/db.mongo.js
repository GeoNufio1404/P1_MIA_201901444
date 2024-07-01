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
    console.log('\n==========================');
    console.log('URI: ', uri);
    const mongoClient = new MongoClient(uri);
    try {
        await mongoClient.connect().then(() => console.log('Conectado a la base de datos'));
        const dbmongo = mongoClient.db(MONGODB_DATABASE);
        const coleccion = dbmongo.collection(collec);
        console.log(`Insertando datos en la colección: ${collec}`);
        const result = await coleccion.insertOne(data);
        console.log(`Datos insertados correctamente: ${result.insertedId}`);
        return result;
    } catch (error) {
        console.error('Error insertData: ', error);
        return error;
    } finally {
        await mongoClient.close();
        console.log('Desconectado de la base de datos\n==========================\n');
    }
}

// Obtiene todos los datos de una colección
async function getCollection(collec) {
    console.log('\n==========================');
    console.log('URI: ', uri);
    const mongoClient = new MongoClient(uri);
    try {
        await mongoClient.connect().then(() => console.log('Conectado a la base de datos'));
        const dbmongo = mongoClient.db(MONGODB_DATABASE);
        const coleccion = dbmongo.collection(collec);
        console.log(`Obteniendo datos de la colección: ${collec}`);
        const result = await coleccion.find({}).toArray();
        console.log(`Datos obtenidos correctamente: ${result.length} registros`);
        return result;
    } catch (error) {
        console.error('Error getCollection: ', error);
        return error;
    } finally {
        await mongoClient.close();
        console.log('Desconectado de la base de datos\n==========================\n');
    }
}

module.exports = {
    insertData,
    getCollection
};