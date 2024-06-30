
// Contenedor_Principal: Función que recibe un componente y lo envuelve en un contenedor principal.
const Contenedor_Principal = (Contenido) => {
    return (
        <div className="container-fixed mx-auto sombra text-center Principal example-row p-2">
            {Contenido}
        </div>
    );
};

// Margen_Contenedor_Secundario: Función que recibe un componente y lo envuelve en un contenedor secundario con margen.
const Margen_Contenedor_Secundario = (CodigoHtml) => {
    return (
        <div className="Fondo p-4">
            <br /><hr className="Principal" /><br />
            {CodigoHtml}
            <br /><hr className="Principal" /><br />
        </div>
    );
};

export { Contenedor_Principal, Margen_Contenedor_Secundario };