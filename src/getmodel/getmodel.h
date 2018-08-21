/*
* Copyright (c)2015 - 2016 Oasis LMF Limited
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions
* are met:
*
*   * Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*
*   * Redistributions in binary form must reproduce the above copyright
*     notice, this list of conditions and the following disclaimer in
*     the documentation and/or other materials provided with the
*     distribution.
*
*   * Neither the original author of this software nor the names of its
*     contributors may be used to endorse or promote products derived
*     from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
* FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
* COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
* OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
* AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF
* THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
* DAMAGE.
*/
/*

Author: Mark Pinkerton  email: mark.pinkerton@oasislmf.org

*/

#ifndef GETMODEL_H_
#define GETMODEL_H_

#include <map>
#include <set>
#include <list>
#include <vector>
#include "../include/oasis.h"
bool operator< (const item &a, const item &i);

struct Result;
struct EventIndex;
struct Weight;
struct AggregateID;

class getmodel {

public:

    getmodel();
    ~getmodel();
    void init(bool zip);
	void doCdf(int event_id);


private:
	
	std::map<int, std::vector<OASIS_FLOAT> > _vulnerabilities;	
    std::map<AREAPERIL_INT, std::set<int> > _vulnerability_ids_by_area_peril;
    std::map<int, EventIndex> _event_index_by_event_id;
	std::map<AREAPERIL_INT, std::map<AREAPERIL_INT,OASIS_FLOAT>> _aggregate_areaperils;
	std::map<int, std::map<AREAPERIL_INT, std::map<int, OASIS_FLOAT>>> _aggregate_vulnerabilities;

	std::set<AREAPERIL_INT> _area_perils;
	std::set<int> _vulnerability_ids;
	std::set<int> _aggregate_vulnerability_ids;
	std::set<AREAPERIL_INT> _aggregate_areaperil_ids;
	std::set<AREAPERIL_INT> _disagg_area_perils;
	std::set<int> _group_ids = { 0 };
	std::set<int> _item_ids = { 0 };

	std::vector<OASIS_FLOAT> _mean_damage_bins;
    std::vector<unsigned char > _compressed_buf;
    std::vector<unsigned char > _uncompressed_buf;
	std::vector<aggregate_item> _aggregate_items;
	std::vector<item> _expanded_items;


	std::vector<Result> _temp_results;
	//Result* _temp_results;
    
	int _num_intensity_bins = -1;
    int _num_damage_bins = -1;

	//aggregate ids larger than non aggregate ids, this is the first id that is aggregate
	int _agg_vul_start = -1;
	int _agg_ap_start = -1;

 
	bool _has_disagg_uncertainty = false;
	bool _has_intensity_uncertainty = false;
    bool _zip = false;


	void getItems();
	void getAggregateAreaPerils();
	void getAggregateVulnerabilities();
	void getCoverages(std::vector<OASIS_FLOAT> &_coverages);
	void expandItems(aggregate_item &a, std::vector<OASIS_FLOAT> &_coverages);
	void outputNewCoverages(std::vector<OASIS_FLOAT> &_coverages);

	void newItems();

    void getVulnerabilities();
    void getDamageBinDictionary();
    void getFootPrints();
	void getIntensityInfo();


	void getIntensityProbs(int event_id, std::map<AREAPERIL_INT, std::vector<OASIS_FLOAT>> &areaperil_intensity);
	void newFootprint(int event_id, AREAPERIL_INT aggregate_areaperil_id, std::vector<EventRow> &new_Footprint);
	void newVulnerability(int aggregate_vulnerability_id, std::vector<OASIS_FLOAT> &new_Vulnerability,
		AREAPERIL_INT areaperil_id);


    void doCdfInner(int event_id);
    void doCdfInnerNoIntensityUncertainty(int event_id);

	//can use getIntensityProbs function to merge functions - apply for zip or not
    void doCdfInnerz(int event_id);
    void doCdfInnerNoIntensityUncertaintyz(int event_id);
	void doCdfAggregate(int event_id);

	void getDisaggregateCdfs(int event_id,
		std::map<AREAPERIL_INT, std::map<int, std::vector<OASIS_FLOAT>>> &results_map,
		std::map<AREAPERIL_INT, std::set<int>> &disaggregated_vul_by_ap);


    void  doResults(
        int &event_id,
		AREAPERIL_INT &areaperil_id,
        std::vector<OASIS_FLOAT> intensity,
		std::map<AREAPERIL_INT, std::set<int>> &vulnerability_ids_by_area_peril);
	void doResultsAggregate(
		int &event_id,
		AREAPERIL_INT aggregate_areaperil_id,
		std::set<int> &aggregate_vulnerability_ids,
		std::map<AREAPERIL_INT, std::map<int, std::vector<OASIS_FLOAT>>> &results_map);
	void  doResultsNoIntensityUncertainty(
		int &event_id,
		AREAPERIL_INT &areaperil_id,
		int intensity_bin_index) ;
	
	static void initOutputStream();
    int getVulnerabilityIndex(int intensity_bin_index, int damage_bin_index) const;
};

#endif // GETMODEL_H_
