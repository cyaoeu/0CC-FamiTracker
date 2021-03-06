/*
** FamiTracker - NES/Famicom sound tracker
** Copyright (C) 2005-2014  Jonathan Liss
**
** 0CC-FamiTracker is (C) 2014-2018 HertzDevil
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
** Library General Public License for more details.  To obtain a
** copy of the GNU Library General Public License, write to the Free
** Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
**
** Any permitted reproduction of these routines, in whole or in part,
** must bear this legend.
*/

#include "InstrumentService.h"
#include "InstrumentTypeImpl.h"
#include "InstrumentIO.h"
#include "Assertion.h"
#include "ModuleException.h"

std::unique_ptr<CInstrument> CInstrumentService::Make(inst_type_t index) const {
	return GetInstrumentType(index).MakeInstrument();
}

std::unique_ptr<CInstrumentIO> CInstrumentService::GetInstrumentIO(inst_type_t index, module_error_level_t err_lv) const {
	return GetInstrumentType(index).GetInstrumentIO(err_lv);
}

const CInstCompiler &CInstrumentService::GetChunkCompiler(inst_type_t index) const {
	return GetInstrumentType(index).GetChunkCompiler();
}

void CInstrumentService::AddType(std::unique_ptr<CInstrumentType> itype) {
	inst_type_t t = itype->GetID();
	types_.try_emplace(t, std::move(itype));
}

void CInstrumentService::AddDefaultTypes() {
	AddType(std::make_unique<CInstrumentType2A03>());
	AddType(std::make_unique<CInstrumentTypeVRC6>());
	AddType(std::make_unique<CInstrumentTypeVRC7>());
	AddType(std::make_unique<CInstrumentTypeFDS >());
	AddType(std::make_unique<CInstrumentTypeN163>());
	AddType(std::make_unique<CInstrumentTypeS5B >());
}

CInstrumentType &CInstrumentService::GetInstrumentType(inst_type_t index) const {
	if (auto it = types_.find(index); it != types_.end())
		return *it->second;

	static CInstrumentTypeNull null_inst;
	DEBUG_BREAK();
	return null_inst;
}
