---
description: |
    API documentation for modules: aqelib, aqelib.chemaxon, aqelib.chemaxon.chemaxon, aqelib.credentials, aqelib.credentials.aws, aqelib.docking, aqelib.docking.smina, aqelib.frametools, aqelib.frametools.frametools, aqelib.functional, aqelib.functional.funcs, aqelib.loggers, aqelib.loggers.chemlog, aqelib.mdft, aqelib.mdft.mdft, aqelib.mdft.mdft_inputs, aqelib.molecular_mechanics, aqelib.molecular_mechanics.relax, aqelib.molecular_mechanics.run_gromacs, aqelib.molecular_mechanics.utils, aqelib.moltools, aqelib.moltools.tools, aqelib.parallel, aqelib.parallel.thread.

header-includes: |
 \usepackage{tikz}
 \usetikzlibrary{positioning}
 \usetikzlibrary{arrows}
 \usetikzlibrary{mindmap}
 \usetikzlibrary{er}

lang: en

classoption: oneside
geometry: margin=1in
papersize: a4

linkcolor: blue
links-as-notes: true
...

\begin{tikzpicture}
    [mindmap,
    grow cyclic,
    every node/.style=concept,
    concept color=teal!40,
    level 1/.append style={level distance=6cm, sibling angle=360/9},
    level 2/.append style={sibling angle=37.5},
    ]
    \node [root concept] {Aqelib}
    child [level distance=5cm, concept color=purple!40, rotate=1]{
        node    {chemaxon}
    }
    child [level distance=5cm, concept color=pink!40, rotate=1]{
        node     {credential}
    }
    child [level distance=5cm, concept color=red!40, rotate=1]{
        node  {docking}%[counterclockwise from=-115]
    }
    child [concept color=blue!40, rotate=1]{
        node     {frametools}
    }
    child [concept color=orange!30, rotate=1]{
        node     {moltools}
    }
    child [concept color=yellow!40, rotate=1]{
        node   {mdft}%[clockwise from=45, level distance=8cm]
    }
    child [concept color=green!40, rotate=1]{
        node  {molecular mechanics}
    }
    child [concept color=green!70, rotate=1]{
        node  {loggers}
    }
    child [concept color=violet!40, rotate=1] {
        node {parallel}
    };
\end{tikzpicture}


![Data Screening Architecture](./doc/data-graph.jpeg)


# Module `aqelib` {#aqelib}




    
## Sub-modules

* [aqelib.chemaxon](#aqelib.chemaxon)
* [aqelib.credentials](#aqelib.credentials)
* [aqelib.docking](#aqelib.docking)
* [aqelib.frametools](#aqelib.frametools)
* [aqelib.functional](#aqelib.functional)
* [aqelib.loggers](#aqelib.loggers)
* [aqelib.mdft](#aqelib.mdft)
* [aqelib.molecular_mechanics](#aqelib.molecular_mechanics)
* [aqelib.moltools](#aqelib.moltools)
* [aqelib.parallel](#aqelib.parallel)






    
# Module `aqelib.chemaxon` {#aqelib.chemaxon}




    
## Sub-modules

* [aqelib.chemaxon.chemaxon](#aqelib.chemaxon.chemaxon)






    
# Module `aqelib.chemaxon.chemaxon` {#aqelib.chemaxon.chemaxon}






    
## Functions


    
### Function `cxcalc_dominant_tautomer_distribution` {#aqelib.chemaxon.chemaxon.cxcalc_dominant_tautomer_distribution}




>     def cxcalc_dominant_tautomer_distribution(
>         mol,
>         ph: float = 7.4
>     ) ‑> pandas.core.frame.DataFrame


cxcalc_dominant_tautomer_distribution get predominance weight

Use Chemaxon cxcalc binary:

```bash
cxcalc dominanttautomerdistribution -p 2 --pH $ph, ${Chem.MolToSmiles(mol)}, -f sdf
```

mol must be ***str*** a <code>json Chem.Mol</code> or ***rdkit.Chem.Mol***

###### Parameters


**```mol```** :&ensp;<code>str</code> or  <code>rdkit.Chem.Mol</code>
:   - str: ***json Chem.Mol***
    - obj: ***rdkit.Chem.Mol***


   rdkit mol or rdkit mol json

**```ph```** :&ensp;<code>float</code>, optional
:   ph is 7.4 by default

###### Returns

<code>pandas.DataFrame</code>
:   pandas.DataFrame if successful, pandas.DataFrame.empty otherwise.

    Set LOGGING_LEVEL=DEBUG to see cxcalc full command for each mol
    if process get stderr, it will be logged as error

###### Raises

<code>Chem.MolToSmiles(mol) is raises safe all exceptions will be logged as exception</code>
:   &nbsp;






    
# Module `aqelib.credentials` {#aqelib.credentials}




    
## Sub-modules

* [aqelib.credentials.aws](#aqelib.credentials.aws)






    
# Module `aqelib.credentials.aws` {#aqelib.credentials.aws}






    
## Functions


    
### Function `get_aws_credentials` {#aqelib.credentials.aws.get_aws_credentials}




>     def get_aws_credentials(
>         items_name: str = 'default'
>     )







    
# Module `aqelib.docking` {#aqelib.docking}




    
## Sub-modules

* [aqelib.docking.smina](#aqelib.docking.smina)






    
# Module `aqelib.docking.smina` {#aqelib.docking.smina}






    
## Functions


    
### Function `generate_smina_conf` {#aqelib.docking.smina.generate_smina_conf}




>     def generate_smina_conf(
>         smina_config: dict,
>         config_dir: str = ''
>     ) ‑> List[tuple]




    
### Function `smina_dock_mol_to_protein` {#aqelib.docking.smina.smina_dock_mol_to_protein}




>     def smina_dock_mol_to_protein(
>         conf_mol: tuple,
>         sminaconf: List[tuple],
>         protein_id: str,
>         aws_credentials: dict = {}
>     ) ‑> pandas.core.frame.DataFrame


smina_dock_mol_to_protein

Use smina binary:

```bash
smina --receptor protein_id.pdb --ligand ${in_mol}.sdf --out ${out_mol}.sdf ${smina_config}
```

mol must be ***str*** a <code>json Chem.Mol</code> or ***rdkit.Chem.Mol***

###### Parameters


**```conf_mol```** :&ensp;<code>Tuple\[str</code> or  `rdkit.Chem.Mol, str] | Tuple[mol, parent_inchikey]`
:   - str: ***json Chem.Mol***
    - obj: ***rdkit.Chem.Mol***


   rdkit mol or rdkit mol json
    - str: ***parent_inchikey***

```python
conf_mol = (mol, "CNCCN(C)n1cc(c2ccccc2)c3ccccc13")
```

**```sminaconf```** :&ensp;<code>List\[tuple]</code>
:   list of key:value:


```python
smina = [
("size_x", 20),
("size_y", 20,)
("size_z", 20,)
("center_x", 6.554,)
("center_y", 43.184,)
("center_z", 51.151)
]
```
Will be converted
```bash
--size_x 20 --size_y 20 --size_z 20 --center_x 6.554 --center_y 43.184 --center_z 51.151
```
**```protein_id```** :&ensp;<code>str</code>
:   protein name


**```aws_credentials```** :&ensp;<code>dict</code>
:   use aqelib.credential.aws.get_aws_credentials
    aws_credentials = {} by default
    needed to get protein_id.pdb

###### Returns


<code>pandas.DataFrame</code>
:   pandas.DataFrame with _DOCKING SUCCESS_ if successful,
    pandas.DataFrame with _SMINA FAILED_ if smina_command does not work
    pandas.DataFrame with _DOCKING add_explicit_hs ERROR_ if obabel did not work

    Set LOGGING_LEVEL=INFO to see smina_command full command for each mol
    if process get stderr, it will be logged as error

###### Raises

Smina_dock_mol_to_protein is raises safe.
<code>All exceptions will be logged as exception</code>
:   &nbsp;

###### Info


Each protein are dowloaded in /tmp only one time.
It will reuse same pdb if proteine_id is already in /tmp

You can put your protein.pdb in /tmp,
it will use this one instead of downloading it

You can custom docking paramatere only with sminaconf input




    
# Module `aqelib.frametools` {#aqelib.frametools}




    
## Sub-modules

* [aqelib.frametools.frametools](#aqelib.frametools.frametools)






    
# Module `aqelib.frametools.frametools` {#aqelib.frametools.frametools}






    
## Functions


    
### Function `bag_to_dataframe` {#aqelib.frametools.frametools.bag_to_dataframe}




>     def bag_to_dataframe(
>         bag,
>         meta: dict = {},
>         verify_meta=False,
>         **concat_kwargs
>     )




    
### Function `concat_dataframe` {#aqelib.frametools.frametools.concat_dataframe}




>     def concat_dataframe(
>         updf: pandas.core.frame.DataFrame,
>         downdf: pandas.core.frame.DataFrame
>     ) ‑> pandas.core.frame.DataFrame


concat two dataframe to one in up side down
return pandas.DataFrame

###### Parameters


**```updf```** :&ensp;<code>pandas.DataFrame</code>
:   Up dataframe


**```downdf```** :&ensp;<code>pandas.DataFrame</code>
:   Down dataframe

###### Returns


<code>pandas.DataFrame</code>
:   Returning one pandas.DataFrame


<code>updf and downdf must be empty pandas.DataFrame at least but not null</code>
:   &nbsp;



    
### Function `dataframe_to_record_dict` {#aqelib.frametools.frametools.dataframe_to_record_dict}




>     def dataframe_to_record_dict(
>         df: pandas.core.frame.DataFrame
>     )







    
# Module `aqelib.functional` {#aqelib.functional}




    
## Sub-modules

* [aqelib.functional.funcs](#aqelib.functional.funcs)






    
# Module `aqelib.functional.funcs` {#aqelib.functional.funcs}






    
## Functions


    
### Function `compose` {#aqelib.functional.funcs.compose}




>     def compose(
>         *functions
>     )







    
# Module `aqelib.loggers` {#aqelib.loggers}




    
## Sub-modules

* [aqelib.loggers.chemlog](#aqelib.loggers.chemlog)






    
# Module `aqelib.loggers.chemlog` {#aqelib.loggers.chemlog}






    
## Functions


    
### Function `disable_rdkit_logging` {#aqelib.loggers.chemlog.disable_rdkit_logging}




>     def disable_rdkit_logging()


Disables RDKit whiny logging.




    
# Module `aqelib.mdft` {#aqelib.mdft}




    
## Sub-modules

* [aqelib.mdft.mdft](#aqelib.mdft.mdft)
* [aqelib.mdft.mdft_inputs](#aqelib.mdft.mdft_inputs)






    
# Module `aqelib.mdft.mdft` {#aqelib.mdft.mdft}

Copyright (C) Aqemia 2020 - All rights reserved.




    
## Functions


    
### Function `get_mdft_dg_sol` {#aqelib.mdft.mdft.get_mdft_dg_sol}




>     def get_mdft_dg_sol(
>         mdft_run_id: str,
>         aws_credentials: dict,
>         workdir: str = '/tmp'
>     )




    
### Function `run_mdft` {#aqelib.mdft.mdft.run_mdft}




>     def run_mdft(
>         solute_in: str,
>         solute_dft_in: str,
>         pose_hash: str,
>         system_name: str,
>         aws_credentials: dict,
>         workdir: str = '/tmp'
>     ) ‑> float




    
### Function `run_mdft_PL_P_L` {#aqelib.mdft.mdft.run_mdft_PL_P_L}




>     def run_mdft_PL_P_L(
>         relax_df: pandas.core.frame.DataFrame,
>         aws_credentials: dict
>     ) ‑> pandas.core.frame.DataFrame




    
### Function `zipdir` {#aqelib.mdft.mdft.zipdir}




>     def zipdir(
>         path,
>         ziph
>     )







    
# Module `aqelib.mdft.mdft_inputs` {#aqelib.mdft.mdft_inputs}

Copyright (C) Aqemia 2020 - All rights reserved.




    
## Functions


    
### Function `set_box_size` {#aqelib.mdft.mdft_inputs.set_box_size}




>     def set_box_size(
>         system_in: str,
>         buffer_layer=10
>     ) ‑> (<class 'int'>, <class 'int'>, <class 'int'>)




    
### Function `write_affinity_input` {#aqelib.mdft.mdft_inputs.write_affinity_input}




>     def write_affinity_input(
>         sytem_pmd
>     ) ‑> str




    
### Function `write_affinity_parameters_file` {#aqelib.mdft.mdft_inputs.write_affinity_parameters_file}




>     def write_affinity_parameters_file(
>         system_in,
>         mdft_dxdydz,
>         mmax=1,
>         solvent_type='tip3p',
>         buffer_layer=10
>     ) ‑> str







    
# Module `aqelib.molecular_mechanics` {#aqelib.molecular_mechanics}




    
## Sub-modules

* [aqelib.molecular_mechanics.relax](#aqelib.molecular_mechanics.relax)
* [aqelib.molecular_mechanics.run_gromacs](#aqelib.molecular_mechanics.run_gromacs)
* [aqelib.molecular_mechanics.utils](#aqelib.molecular_mechanics.utils)






    
# Module `aqelib.molecular_mechanics.relax` {#aqelib.molecular_mechanics.relax}






    
## Functions


    
### Function `relax_pose` {#aqelib.molecular_mechanics.relax.relax_pose}




>     def relax_pose(
>         mol: str,
>         protein_id: str,
>         protein_coord_hash: str
>     ) ‑> dict




    
### Function `relax_posesdf` {#aqelib.molecular_mechanics.relax.relax_posesdf}




>     def relax_posesdf(
>         poses_df: pandas.core.frame.DataFrame,
>         meta: dict = {}
>     ) ‑> pandas.core.frame.DataFrame







    
# Module `aqelib.molecular_mechanics.run_gromacs` {#aqelib.molecular_mechanics.run_gromacs}






    
## Functions


    
### Function `adapt_box_vector_to_coordinates` {#aqelib.molecular_mechanics.run_gromacs.adapt_box_vector_to_coordinates}




>     def adapt_box_vector_to_coordinates(
>         system_pmd,
>         buffer: float
>     )




    
### Function `get_max_distances_from_center` {#aqelib.molecular_mechanics.run_gromacs.get_max_distances_from_center}




>     def get_max_distances_from_center(
>         coordinates: str
>     ) ‑> Tuple[int, int, int]




    
### Function `get_nsteps_from_gromacs_log` {#aqelib.molecular_mechanics.run_gromacs.get_nsteps_from_gromacs_log}




>     def get_nsteps_from_gromacs_log(
>         logfile
>     ) ‑> int




    
### Function `relax_with_gromacs` {#aqelib.molecular_mechanics.run_gromacs.relax_with_gromacs}




>     def relax_with_gromacs(
>         run_dir: str,
>         system_pmd,
>         total_minimization_cycles: int
>     )







    
# Module `aqelib.molecular_mechanics.utils` {#aqelib.molecular_mechanics.utils}

Copyright (C) Aqemia 2020 - All rights reserved.




    
## Functions


    
### Function `calculate_epsilon_ij` {#aqelib.molecular_mechanics.utils.calculate_epsilon_ij}




>     def calculate_epsilon_ij(
>         atoms_i,
>         atoms_j,
>         method='LB'
>     )


Returns epsilon_ij value by applying Lorentz-Berthelot
(default) combining rule

###### Parameters


**```atoms_a```** :&ensp;<code>dict</code>
:   dictionary containing properties of atom I


**```atoms_b```** :&ensp;<code>dict</code>
:   dictionary containing properties of atom J


**```method```** :&ensp;<code>str</code>, optional
:   Method name for calculating epsilon_ij.
    Only "LB" is supported currently.
    The default is 'LB'.

###### Returns


**```epsilon_ij```** :&ensp;<code>float</code>
:   value of epsilon_ij



    
### Function `calculate_sigma_ij` {#aqelib.molecular_mechanics.utils.calculate_sigma_ij}




>     def calculate_sigma_ij(
>         atoms_i,
>         atoms_j,
>         method='LB'
>     )


Returns sigma_ij value by applying Lorentz-Berthelot
    (default) or geometric combining rule

###### Parameters


**```atoms_i```** :&ensp;<code>dict</code>
:   dictionary containing properties of atom I


**```atoms_j```** :&ensp;<code>dict</code>
:   dictionary containing properties of atom J


**```method```** :&ensp;<code>str</code>, optional
:   Method name for calculating sigma_ij.
    Only "LB" and "geometric" are supported currently.
    The default is 'LB'.

###### Returns


**```sigma_ij```** :&ensp;<code>float</code>
:   value of sigma_ij



    
### Function `compute_distance_matrix` {#aqelib.molecular_mechanics.utils.compute_distance_matrix}




>     def compute_distance_matrix(
>         molecule_a,
>         molecule_b
>     )




    
### Function `compute_eint_from_top_crd` {#aqelib.molecular_mechanics.utils.compute_eint_from_top_crd}




>     def compute_eint_from_top_crd(
>         parmed_pose_l,
>         parmed_pose_p
>     ) ‑> (<class 'float'>, <class 'float'>, <class 'float'>)


Computes interaction energy between two molecules

###### Parameters

**```parmed_pose_l```** :&ensp;<code>object</code>
:   parmed object


**```parmed_pose_p```** :&ensp;<code>object</code>
:   parmed object

###### Returns


**```compute_interaction_energy```** :&ensp;<code>tuple</code>
:   &nbsp;


`The interaction energy between two molecules, in kcal/mol`
:   &nbsp;



    
### Function `compute_electrostatic_energy` {#aqelib.molecular_mechanics.utils.compute_electrostatic_energy}




>     def compute_electrostatic_energy(
>         molecule_a: list,
>         molecule_b: list,
>         relative_permittivity: float = 1
>     ) ‑> float


Computes electrostatic energy between two molecules.

###### Parameters


**```molecule_a```** :&ensp;<code>list</code>
:   list of atoms dictionaries containing properties of atom i.


**```molecule_b```** :&ensp;<code>list</code>
:   list of atoms dictionaries containing properties of atom i.


**```relative_permittivity```** :&ensp;<code>list</code>
:   The default is 1.

###### Returns


`electrostatic_energy_kcal:`
:   &nbsp;


`the electrostatic energy between two molecules, in kcal/mol`
:   &nbsp;



    
### Function `compute_interaction_energy` {#aqelib.molecular_mechanics.utils.compute_interaction_energy}




>     def compute_interaction_energy(
>         molecule_a: list,
>         molecule_b: list
>     ) ‑> (<class 'float'>, <class 'float'>, <class 'float'>)


Computes interaction energy between two molecules.

###### Parameters


**```molecule_a```** :&ensp;<code>list</code>
:   list of atoms dictionary containing properties of atom i.


**```molecule_b```** :&ensp;<code>list</code>
:   list of atoms dictionary containing properties of atom i.

###### Returns


`interaction_energy, lennard_jones_energy, electrostatic_energy:`
:   &nbsp;


`the interaction energies between two molecules in kcal/mol`
:   &nbsp;



    
### Function `compute_lennard_jones_energy` {#aqelib.molecular_mechanics.utils.compute_lennard_jones_energy}




>     def compute_lennard_jones_energy(
>         molecule_a: list,
>         molecule_b: list
>     ) ‑> float


Computes Lennard-Jones energy between two molecules.

###### Parameters


**```molecule_a```** :&ensp;<code>list</code>
:   list of atoms dictionary containing properties of atom i.


**```molecule_b```** :&ensp;<code>list</code>
:   list of atoms dictionary containing properties of atom i.

###### Returns


`lennard_jones_energy_kcal:`
:   &nbsp;


`the Lennard-Jones energy between two molecules, in kcal/mol`
:   &nbsp;



    
### Function `create_dict_per_atom` {#aqelib.molecular_mechanics.utils.create_dict_per_atom}




>     def create_dict_per_atom(
>         parmed_pose: str
>     ) ‑> list


Create a dictionary for each atom in a molecule
from a topology file and a coordinate file

###### Parameters


**```topology_file```** :&ensp;<code>str</code>
:   Topology file of the molecule


**```coordinate_file```** :&ensp;<code>str</code>
:   Coordinate file of the molecule


**```parmed_pose```** :&ensp;<code>parmed object</code>
:   &nbsp;

###### Returns


**```atoms```** :&ensp;<code>list</code>
:   &nbsp;


<code>list</code> of `atom dictionaries containing :`
:   - charge
    - atomic_number
    - atom_reference
    - sigma
    - epsilon
    - x_coord
    - y_coord
    - z_coord



    
### Function `get_etot` {#aqelib.molecular_mechanics.utils.get_etot}




>     def get_etot(
>         system_parmed
>     ) ‑> float




    
### Function `get_mol_charges` {#aqelib.molecular_mechanics.utils.get_mol_charges}




>     def get_mol_charges(
>         molecule: list
>     ) ‑> <built-in function array>


Parameters
-----

**```molecule```** :&ensp;<code>list</code>
:   list of atoms dictionary containing properties of atom i

###### Returns


**```charges```** :&ensp;<code>np.array</code>
:   &nbsp;



    
### Function `get_mol_coords` {#aqelib.molecular_mechanics.utils.get_mol_coords}




>     def get_mol_coords(
>         molecule
>     )


Return list of atom coordinates:

- one list for x_coords,
- one y_coords,
- one for z_coords

###### Parameters


**```molecule```** :&ensp;<code>list</code>
:   list of atoms dictionary containing properties of atom i

###### Returns

**```x_coords```** :&ensp;<code>list</code>
:   &nbsp;


**```y_coords```** :&ensp;<code>list</code>
:   &nbsp;


**```z_coords```** :&ensp;<code>list</code>
:   &nbsp;



    
### Function `get_mol_epsilon` {#aqelib.molecular_mechanics.utils.get_mol_epsilon}




>     def get_mol_epsilon(
>         molecule: list
>     ) ‑> <built-in function array>


Parameters
-----

**```molecule```** :&ensp;<code>list</code> of <code>atoms dictionary containing properties</code> of <code>atom i</code>
:   &nbsp;

###### Returns


<code>epsilons</code>
:   &nbsp;



    
### Function `get_mol_sigma` {#aqelib.molecular_mechanics.utils.get_mol_sigma}




>     def get_mol_sigma(
>         molecule
>     )


Return list of atom sigmas

###### Parameters


**```molecule```** :&ensp;<code>list</code>
:   list of atoms dictionary containing properties of atom i

###### Returns


    sigmas : list

    
### Function `parametrize_ligand` {#aqelib.molecular_mechanics.utils.parametrize_ligand}




>     def parametrize_ligand(
>         dockedmol: object,
>         workdir: str
>     ) ‑> object




    
### Function `parametrize_protein` {#aqelib.molecular_mechanics.utils.parametrize_protein}




>     def parametrize_protein(
>         protein_pdb_path: str,
>         workdir: str
>     ) ‑> object







    
# Module `aqelib.moltools` {#aqelib.moltools}




    
## Sub-modules

* [aqelib.moltools.tools](#aqelib.moltools.tools)






    
# Module `aqelib.moltools.tools` {#aqelib.moltools.tools}






    
## Functions


    
### Function `check_mol` {#aqelib.moltools.tools.check_mol}




>     def check_mol(
>         mol: rdkit.Chem.rdchem.Mol
>     )




    
### Function `enumerate_stereoisomers` {#aqelib.moltools.tools.enumerate_stereoisomers}




>     def enumerate_stereoisomers(
>         inputs: Tuple[str, rdkit.Chem.rdchem.Mol]
>     ) ‑> List[Tuple[str, rdkit.Chem.rdchem.Mol]]


Enumerate stereoisomers from input mol
return List of Chem.Mol
List[Chem.Mol] list

- Parameters:
mol      (Chem.Mol): input molecule to find stereoisomers

- Returns:
List[Chem.Mol]: Returning all stereoisomers in Chem.Mol

mol cannot be None
Traceback (most recent call last):
...
TypeError: enumerate_stereoisomers() missing 1 required positional argument: 'mol'

    
### Function `generate_conformers` {#aqelib.moltools.tools.generate_conformers}




>     def generate_conformers(
>         tauto_mol: tuple,
>         numgenerate: int = 300,
>         numconfs: int = 1
>     ) ‑> pandas.core.frame.DataFrame




    
### Function `hash_mol` {#aqelib.moltools.tools.hash_mol}




>     def hash_mol(
>         mol: str,
>         objtype: type = builtins.int
>     )




    
### Function `hash_str` {#aqelib.moltools.tools.hash_str}




>     def hash_str(
>         inputfile: str,
>         objtype: type = builtins.str
>     ) ‑> str




    
### Function `hash_to_int` {#aqelib.moltools.tools.hash_to_int}




>     def hash_to_int(
>         hash_val: str
>     )




    
### Function `mol_to_dataframe` {#aqelib.moltools.tools.mol_to_dataframe}




>     def mol_to_dataframe(
>         mol: rdkit.Chem.rdchem.Mol
>     ) ‑> pandas.core.frame.DataFrame




    
### Function `mols_to_dataframe` {#aqelib.moltools.tools.mols_to_dataframe}




>     def mols_to_dataframe(
>         inputs: List[Tuple[str, rdkit.Chem.rdchem.Mol]]
>     ) ‑> pandas.core.frame.DataFrame




    
### Function `normalize_mol_to_dict` {#aqelib.moltools.tools.normalize_mol_to_dict}




>     def normalize_mol_to_dict(
>         inputs: Tuple[str, rdkit.Chem.rdchem.Mol]
>     ) ‑> dict




    
### Function `round_jsonmol` {#aqelib.moltools.tools.round_jsonmol}




>     def round_jsonmol(
>         jsonmol: str
>     ) ‑> str




    
### Function `smiles_to_mol` {#aqelib.moltools.tools.smiles_to_mol}




>     def smiles_to_mol(
>         smiles: str
>     ) ‑> Tuple[str, rdkit.Chem.rdchem.Mol]


Return the Chem.Mol of smile string.
Chem.Mol object

###### Parameters


**```smile```** :&ensp;<code>str</code>
:   input string

###### Returns:


Tuple[str, Chem.Mol]:
    Returning smiles in str and his associated mol in rdkit.Chem.Mol

###### Raises


    Smiles cannot be None

    
### Function `smiles_to_standard_mol` {#aqelib.moltools.tools.smiles_to_standard_mol}




>     def smiles_to_standard_mol(
>         smile: str
>     ) ‑> rdkit.Chem.rdchem.Mol




    
### Function `standardize_mol` {#aqelib.moltools.tools.standardize_mol}




>     def standardize_mol(
>         inputs: Tuple[str, rdkit.Chem.rdchem.Mol]
>     ) ‑> Tuple[str, rdkit.Chem.rdchem.Mol]




    
### Function `standardize_mols` {#aqelib.moltools.tools.standardize_mols}




>     def standardize_mols(
>         mols: List[Tuple[str, rdkit.Chem.rdchem.Mol]]
>     ) ‑> List[Tuple[str, rdkit.Chem.rdchem.Mol]]




    
### Function `tautomer_distribution` {#aqelib.moltools.tools.tautomer_distribution}




>     def tautomer_distribution(
>         mols: List[rdkit.Chem.rdchem.Mol]
>     ) ‑> pandas.core.frame.DataFrame


Compute tautomer distribution of mols list
return pandas.DataFrame

- Parameters:
mols        (List[Chem.Mol]): Up dataframe

- Returns:
pandas.DataFrame: Returning one pandas.DataFrame




    
# Module `aqelib.parallel` {#aqelib.parallel}




    
## Sub-modules

* [aqelib.parallel.thread](#aqelib.parallel.thread)






    
# Module `aqelib.parallel.thread` {#aqelib.parallel.thread}






    
## Functions


    
### Function `map_parallel` {#aqelib.parallel.thread.map_parallel}




>     def map_parallel(
>         f,
>         iter,
>         max_parallel=8
>     )


Just like map(f, iter) but each is done in a separate thread.



-----
Generated by *pdoc* 0.9.2 (<https://pdoc3.github.io>).
